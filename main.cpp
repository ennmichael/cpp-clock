#include "clock.h"
#include "sdl_plus_plus/resource.h"
#include "sdl_plus_plus/drawing.h"
#include "sdl_plus_plus/flow.h"
#include "SDL2/SDL.h"
#include <iostream>

int main() 
{
    using namespace Sdl;
    using namespace Clock;
    
    constexpr auto Width = 300;
    constexpr auto Height = 300;
    
    try
    {
        Control ctl { }; // Control the SDL subsystems
        ctl.pass(); // Suppress the warning
        
        Screen_properties props { }; // What our window will look like
        
        props.title = "Clock";
        props.width = Width;
        props.height = Height; // Set up...
        
        Screen scrn { props };
        
        Full_clock clck { };
        
        Main_loop ml 
        {
            [&scrn, &clck]()
            { // Do something
                constexpr Point clock_pos { Width / 2, Height / 2 };
                
                for (const auto& line : clck.get_lines(clock_pos))
                    scrn.add_draw(line, { 0, 0, 0, 255 });
                
                clck.update();
                scrn.redraw({ 255, 255, 255, 255 });
            }
        };
        
        ml.start();
    }
    catch (Sdl_exception& e)
    {
        std::cout << "Sdl exception: ";
        std::cout << e.what() << '\n';
    }
    catch (...)
    {
        throw; // Tell me what else could've gone wrong
    }
}
