#include "clock.h"

namespace Clock
{
    std::tm get_tm_now() noexcept
    {
        auto tt = Std_clock::to_time_t(Std_clock::now());
        return *std::localtime(&tt);
    }
    
    Hand make_hour_hand(int len) noexcept
    {
        return { len, 12, 
            [](const auto& tm) 
            {
                if (tm.tm_hour >= 12)
                    return tm.tm_hour - 12;
                else 
                    return tm.tm_hour;
            } };
    }
    
    Hand make_minute_hand(int len) noexcept
    {
        return { len, 60, [](const auto& tm) { return tm.tm_min; } };
    }
    
    Hand make_second_hand(int len) noexcept
    {
        return { len, 60, [](const auto& tm) { return tm.tm_sec; } };
    }
    
    Hand::Hand(int length, int max, const Time_extract_fun& extract) noexcept
        : m_length { length }
        , m_max { max }
        , m_extract { extract }
    {
        update();
    }
    
    void Hand::update() noexcept
    {
        m_angle.value = - (m_extract(get_tm_now()) * 2 * Pi) / m_max - Pi;
    }
    
    Sdl::Line Hand::get_line(Sdl::Point where) const noexcept
    {
        return { where, m_angle, m_length };
    }
    
    void Full_clock::update() noexcept
    {
        for (auto& hand : m_hands)
            hand.update();
    }
    
    std::vector<Sdl::Line> Full_clock::get_lines(
        Sdl::Point where) const noexcept
    {
        std::vector<Sdl::Line> result { };
        
        for (const auto& hand : m_hands)
            result.push_back(hand.get_line(where));
        
        return result;
    }
}
