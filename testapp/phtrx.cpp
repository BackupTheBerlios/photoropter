/*

  phtrx: Photoropter demo application

  Copyright (C) 2010 Robert Fendt

  Usage example :
  phtrx --gain-func emor --param-aspect 1.5333 --vignetting 0:0:-0.3 --ptlens 0:0.00987:-0.05127 in.jpg out.jpg

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "parseconf.h"
#include "transform_wrapper.h"

#include <photoropter/version.h>

#include <ctime>
#include <iostream>
#include <memory>

const char APP_NAME[] = "phtrx";

int main(int argc, char* argv[])
{
    Settings settings;
    std::cerr << "This is " << APP_NAME << std::endl;
    std::cerr << "Using Photoropter version " << phtr::PHTR_VERSION << std::endl;

    if (!parse_command_line(argc, argv, settings))
    {
        std::cerr << "Command line error." << std::endl;
        return 1;
    }
    else
    {
        std::cerr << "Load file and set up transformation." << std::endl;
        std::auto_ptr<TransformWrapperBase> tf(TransformWrapperBase::get_instance(settings));

        std::cerr << "Perform transformation... ";
        time_t t0 = time(0);
        tf->do_transform();
        time_t t1 = time(0);
        std::cerr << "done (time taken: " << difftime(t1, t0) << " seconds)." << std::endl;

        std::cerr << "Save output file." << std::endl;
        tf->save();

        return 0;
    }

}
