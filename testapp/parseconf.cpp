/*

  phtrtest: Photoropter demo application

  Copyright (C) 2010 Robert Fendt

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

#include <iostream>

#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
namespace po = boost::program_options;

#include "parseconf.h"

bool parse_command_line(int argc, char* argv[], Settings& settings)
{

    try
    {

        po::options_description opt_desc("Allowed options");
        opt_desc.add_options()
        ("help,h", "show options")
        ("ptlens", po::value<std::string>(), "Set PTLens correction model parameters: a:b:c[:x0:y0]")
        ("vignetting", po::value<std::string>(), "Set vignetting correction parameters: a:b:c[:x0:y0]")
        ("param-aspect", po::value<double>(), "Aspect ratio used for parameter calibration")
        ("param-crop", po::value<double>(), "Crop factor used for parameter calibration")
        ("image-crop", po::value<double>(), "Diagonal image crop factor")
        ("sub-rect", po::value<std::string>(), "Clip a sub-rectangle from the image: x0:y0:width:height")
        ("gain-func", po::value<std::string>(), "Type of gain function:\n"
         "  srgb    - sRGB gamma (default)\n"
         "  gamma   - generic gamma\n"
         "  emor    - EMOR\n"
         "  invemor - inverse EMOR.")
        ("gamma", po::value<double>(), "Gamma value (default: assume sRGB gamma)")
        ("emor-params", po::value<std::string>(), "EMOR parameters: h1[:h2[:h3...]]")
        ("oversample", po::value<unsigned>(), "Sampling factor (>= 1)")
        ("input-file", po::value<std::string>(), "Input file")
        ("output-file", po::value<std::string>(), "Output file");

        po::positional_options_description pos_opts;
        pos_opts.add("input-file", 1);
        pos_opts.add("output-file", 1);

        po::variables_map options_map;
        po::store(po::command_line_parser(argc, argv).
                  options(opt_desc).positional(pos_opts).run(), options_map);
        po::notify(options_map);

        if (options_map.count("help"))
        {
            std::cerr << opt_desc << std::endl;
            return false;
        }

        if (options_map.count("param-crop"))
        {
            settings.param_crop = options_map["param-crop"].as<double>();
        }

        if (options_map.count("param-aspect"))
        {
            settings.param_aspect = options_map["param-aspect"].as<double>();
        }

        if (options_map.count("image-crop"))
        {
            settings.image_crop = options_map["image-crop"].as<double>();
        }

        if (options_map.count("input-file"))
        {
            settings.inp_file = options_map["input-file"].as<std::string>();
        }
        else
        {
            std::cerr << "Error: no input file given" << std::endl;
            return false;
        }

        if (options_map.count("output-file"))
        {
            settings.outp_file = options_map["output-file"].as<std::string>();
        }
        else
        {
            std::cerr << "Error: no output file given" << std::endl;
            return false;
        }

        if (options_map.count("ptlens"))
        {
            settings.ptlens_corr = true;

            typedef boost::tokenizer<boost::char_separator<char> > tokenizer_t;
            typedef boost::char_separator<char> separator_t;

            std::string param_string = options_map["ptlens"].as<std::string>();

            separator_t sep(":;");
            tokenizer_t tokens(param_string, sep);

            size_t param_idx(0);
            for (tokenizer_t::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
            {
                std::stringstream sstr(*it);
                sstr >> settings.ptlens_params[param_idx++];
            }

            if (!(param_idx == 3 || param_idx == 5))
            {
                std::cerr << "Error: incorrent number of parameters for PTLens correction" << std::endl;
                return false;
            }

            std::cerr << "Performing PTLens correction: "
                      << settings.ptlens_params[0] << ":"
                      << settings.ptlens_params[1] << ":"
                      << settings.ptlens_params[2] << ":"
                      << settings.ptlens_params[3] << ":"
                      << settings.ptlens_params[4] << std::endl;
        }

        if (options_map.count("vignetting"))
        {
            settings.vignetting_corr = true;

            typedef boost::tokenizer<boost::char_separator<char> > tokenizer_t;
            typedef boost::char_separator<char> separator_t;

            std::string param_string = options_map["vignetting"].as<std::string>();

            separator_t sep(":;");
            tokenizer_t tokens(param_string, sep);

            size_t param_idx(0);
            for (tokenizer_t::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
            {
                std::stringstream sstr(*it);
                sstr >> settings.vignetting_params[param_idx++];
            }

            if (!(param_idx == 3 || param_idx == 5))
            {
                std::cerr << "Error: incorrent number of parameters for Vignetting correction" << std::endl;
                return false;
            }

            std::cerr << "Performing Vignetting correction: "
                      << settings.vignetting_params[0] << ":"
                      << settings.vignetting_params[1] << ":"
                      << settings.vignetting_params[2] << ":"
                      << settings.vignetting_params[3] << ":"
                      << settings.vignetting_params[4] << std::endl;
        }

        if (options_map.count("sub-rect"))
        {
            typedef boost::tokenizer<boost::char_separator<char> > tokenizer_t;
            typedef boost::char_separator<char> separator_t;

            std::string param_string = options_map["sub-rect"].as<std::string>();

            separator_t sep(":;");
            tokenizer_t tokens(param_string, sep);

            std::vector<size_t> rect_params(4, 0);

            size_t param_idx(0);
            for (tokenizer_t::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
            {
                std::stringstream sstr(*it);
                sstr >> rect_params[param_idx++];
            }

            if (!(param_idx == 4))
            {
                std::cerr << "Error: incorrent number of parameters for sub rectangle" << std::endl;
                return false;
            }

            settings.sub_rect_x0 = rect_params[0];
            settings.sub_rect_y0 = rect_params[1];
            settings.sub_rect_w = rect_params[2];
            settings.sub_rect_h = rect_params[3];
            settings.sub_rect = true;
        }

        if (options_map.count("gain-func"))
        {
            std::string opt = options_map["gain-func"].as<std::string>();
            if (opt == "srgb")
            {
                settings.gainfunc = GainFunc::srgb;
            }
            else if (opt == "gamma")
            {
                settings.gainfunc = GainFunc::gamma;
            }
            else if (opt == "emor")
            {
                settings.gainfunc = GainFunc::emor;
            }
            if (opt == "invemor")
            {
                settings.gainfunc = GainFunc::invemor;
            }
        }

        if (options_map.count("emor-params"))
        {
            typedef boost::tokenizer<boost::char_separator<char> > tokenizer_t;
            typedef boost::char_separator<char> separator_t;

            std::string param_string = options_map["emor-params"].as<std::string>();

            separator_t sep(":;");
            tokenizer_t tokens(param_string, sep);

            for (tokenizer_t::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
            {
                double val;
                std::stringstream sstr(*it);
                sstr >> val;
                settings.emor_coeffs.push_back(val);
            }

        }

        if (options_map.count("gamma"))
        {
            settings.gamma = options_map["gamma"].as<double>();
        }

        if (options_map.count("oversample"))
        {
            settings.oversampling = options_map["oversample"].as<unsigned>();
        }

    }
    catch (po::unknown_option& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "Try option '--help'" << std::endl;
        return false;
    }
    catch (po::invalid_command_line_syntax& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    return true;
}
