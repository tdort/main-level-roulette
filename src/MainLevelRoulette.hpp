#pragma once

#include <Geode/Geode.hpp>
#include <vector>
#include <algorithm>
#include <random>

using namespace geode::prelude;

// Total count of official "main" levels, Stereo Madness (1) through Dash (22).
// If a future GD update adds another main level, bump this number.
constexpr int MAIN_LEVEL_COUNT = 22;

class MainLevelRoulette {
public:
    static MainLevelRoulette* get() {
        static MainLevelRoulette instance;
        return &instance;
    }

    // Percent required on the current attempt to advance to the next level.
    static constexpr float PASS_THRESHOLD = 5.0f;

    // Starts a fresh run: shuffles all main levels and loads the first one.
    void start() {
        m_pool.clear();
        for (int i = 1; i <= MAIN_LEVEL_COUNT; i++) {
            m_pool.push_back(i);
        }
        std::shuffle(m_pool.begin(), m_pool.end(), std::mt19937(std::random_device{}()));

        m_index = 0;
        m_active = true;

        loadCurrentLevel();
    }

    void stop() {
        m_active = false;
    }

    bool isActive() const { return m_active; }

    // The GD internal level ID (1-22) of whatever we're currently on.
    int currentLevelID() const {
        if (m_index < 0 || m_index >= static_cast<int>(m_pool.size())) return -1;
        return m_pool[m_index];
    }

    // 1-based position in the roulette, e.g. "level 4 of 22".
    int currentPosition() const { return m_index + 1; }

    int totalLevels() const { return static_cast<int>(m_pool.size()); }

    // Call this whenever the player's progress on the current attempt updates
    // (e.g. from destroyPlayer, or a live percent-tick hook if you add one).
    void onPercentUpdate(float percent) {
        if (!m_active) return;
        if (percent >= PASS_THRESHOLD) {
            advance();
        }
    }

    // Call this on a full level completion (100%) - always advances.
    void onLevelComplete() {
        if (!m_active) return;
        advance();
    }

    void advance() {
        m_index++;
        if (m_index >= static_cast<int>(m_pool.size())) {
            m_active = false;
            Notification::create(
                "Main Level Roulette complete! You cleared all 22 levels.",
                NotificationIcon::Success
            )->show();
            return;
        }
        loadCurrentLevel();
    }

private:
    std::vector<int> m_pool;
    int m_index = 0;
    bool m_active = false;

    void loadCurrentLevel();
};
