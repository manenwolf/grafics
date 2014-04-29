#include "EasyImage.h"
#include "ini_configuration.hh"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "grafic/primitives.h"



img::EasyImage generate_image(const ini::Configuration &configuration)
{
    vec2f p1(0.0,0.0);
    vec2f p2(20.0,20.0);
    Line myline();


	unsigned int image_w = configuration["ImageProperties"]["width"].as_int_or_default(256);
	unsigned int image_h = configuration["ImageProperties"]["height"].as_int_or_default(256);
	std::cout << image_w << image_h << std::endl;

	img::EasyImage image(image_w,image_h);

	std::string type = configuration["General"]["type"].as_string_or_default("dieter is een topper");
	std::cout << type << std::endl;
	if( type == "IntroColorRectangle"){
		for(unsigned int i = 0; i < image_h; i++){
			for(unsigned int j = 0; j < image_w; j++){
				image(i,j).red = i;
				image(i,j).green = j;
				image(i,j).blue = (i+j)%256;
			}
		}
	}

	
	else if(type == "IntroBlocks"){

		std::vector<double> white = configuration["BlockProperties"]["colorWhite"];
		std::vector<double> black = configuration["BlockProperties"]["colorBlack"];
		unsigned int numblocks_x  = configuration["BlockProperties"]["nrXBlocks"].as_int_or_die();
		unsigned int numblocks_y  = configuration["BlockProperties"]["nrYBlocks"].as_int_or_die();

		double block_w = image_w/numblocks_x;
		double block_h = image_h/numblocks_y;

		for(unsigned int i = 0; i < image_h; i++){
			for(unsigned int j = 0; j < image_w; j++){
				int block_x = j/(int)block_w;
				int block_y = i/(int)block_h;
		
				if((block_x+block_y)%2 == configuration["BlockProperties"]["invertColors"].as_bool_or_default(false)){
					image(i,j).red   = white[0]*265;
					image(i,j).green = white[1]*265;
					image(i,j).blue  = white[2]*265;
				}else{
					image(i,j).red   = black[0]*265;
					image(i,j).green = black[1]*265;
					image(i,j).blue  = black[2]*265;
				}
			}
		}
	}
    img::Color kleur(20,80,50);
    image.draw_line(0,0,20,20,kleur);
	return image;
}


int main(int argc, char const* argv[])
{
        int retVal = 0;
        try
        {
                for(int i = 1; i < argc; ++i)
                {
			std::cout << "test" << argv[i] << std::endl;
                        ini::Configuration conf;
                        try
                        {
                                std::ifstream fin(argv[i]);
                                fin >> conf;
                                fin.close();
                        }
                        catch(ini::ParseException& ex)
                        {
                                std::cerr << "Error parsing file: " << argv[i] << ": " << ex.what() << std::endl;
                                retVal = 1;
                                continue;
                        }

                        img::EasyImage image = generate_image(conf);
                        if(image.get_height() > 0 && image.get_width() > 0)
                        {
                                std::string fileName(argv[i]);
                                std::string::size_type pos = fileName.rfind('.');
                                if(pos == std::string::npos)
                                {
                                        //filename does not contain a '.' --> append a '.bmp' suffix
                                        fileName += ".bmp";
                                }
                                else
                                {
                                        fileName = fileName.substr(0,pos) + ".bmp";
                                }
                                try
                                {
                                        std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                                        f_out << image;

                                }
                                catch(std::exception& ex)
                                {
                                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                                        retVal = 1;
                                }
                        }
                        else
                        {
                                std::cout << "Could not generate image for " << argv[i] << std::endl;
                        }
                }
        }
        catch(const std::bad_alloc &exception)
        {
    		//When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
    		//Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
    		//(Unless of course you are already consuming the maximum allowed amount of memory) 
    		//If your engine does NOT adhere to this requirement you risk losing points because then our scripts will 
		//mark the test as failed while in reality it just needed a bit more memory
                std::cerr << "Error: insufficient memory" << std::endl;
                retVal = 100;
        }
        return retVal;
}
