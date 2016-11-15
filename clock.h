#pragma once

#include "sdl_plus_plus/drawing.h"
#include <ctime>
#include <functional>
#include <chrono>
#include <array>

namespace Clock
{
    constexpr auto Pi = 3.141592653589793;
    
    using Time_extract_fun = std::function<int(const std::tm&)>;
    using Std_clock = std::chrono::system_clock;
    
    class Hand;
    
    std::tm get_tm_now() noexcept;
    
    Hand make_hour_hand(int) noexcept;
    Hand make_minute_hand(int) noexcept;
    Hand make_second_hand(int) noexcept;
    
    class Hand
    {
    public:
        Hand(int, int, const Time_extract_fun&) noexcept;
        
        void update() noexcept;
        Sdl::Line get_line(Sdl::Point) const noexcept;
        
    private:
        int m_length { };
        int m_max { };
        Time_extract_fun m_extract { };  
        Sdl::Angle_rad m_angle { }; // ???
    };
    
    class Full_clock
    {
    public:
        void update() noexcept;
        std::vector<Sdl::Line> get_lines(Sdl::Point) const noexcept;
        
    private:
        std::vector<Hand> m_hands {
            make_hour_hand(60), make_minute_hand(90), make_second_hand(110)
        };
    };
}
