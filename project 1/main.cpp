#include<stdio.h>
#include<stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"

unsigned char processing_image(unsigned char *background,unsigned char *foreground, unsigned char *weather,int width, int height,int channel3, int channel4)
{
	int gap;
	for(int i = 0; i<height;i++)
	{
		for(int j = 0; j < width;j++)
		{
			gap = 0;
			gap = gap + abs(background[i*width*channel4 + j * channel4 + 0] - foreground[i*width*channel4 + j * channel4 + 0]);
			gap = gap + abs(background[i*width*channel4 + j * channel4 + 1] - foreground[i*width*channel4 + j * channel4 + 1]);
			gap = gap + abs(background[i*width*channel4 + j * channel4 + 2] - foreground[i*width*channel4 + j * channel4 + 2]);
			gap = gap + abs(background[i*width*channel4 + j * channel4 + 3] - foreground[i*width*channel4 + j * channel4 + 3]);
	
			if (gap > 150)
			{
				weather[i*width*channel3 + j * channel3 + 0] = foreground[i*width*channel4 + j * channel4 + 0];
				weather[i*width*channel3 + j * channel3 + 1] = foreground[i*width*channel4 + j * channel4 + 1];
				weather[i*width*channel3 + j * channel3 + 2] = foreground[i*width*channel4 + j * channel4 + 2];
			}
		}
	}
}

int main()
{

    
    char save_path[] = "./images/result_image.png";
    
	char path_background[] = "./images/background.png";
	char path_foreground[] = "./images/foreground.png";
	char path_weather[] = "./images/weather_forecast-resized.jpg";
	
	//Load background
	int width1, height1, channel1;
	unsigned char *background = stbi_load(path_background, &width1, &height1, &channel1, 0);
	if ( background == NULL )
	{
		printf("\ nCan't load background \n");
		exit(1);
	}
	printf ("Background Width = %d Height = %d Channel = %d\n", width1 , height1 , channel1 );
	
	
	
	//Load foreground
	int width2, height2, channel2;
	unsigned char *foreground = stbi_load(path_foreground, &width2, &height2, &channel2, 0);
	if ( foreground == NULL )
	{
		printf("\ nCan't load foreground \n");
		exit(1);
	}
	printf ("Foreground Width = %d Height = %d Channel = %d\n", width2 , height2 , channel2 );
	
	
	
	//Load weather_forecase
	int width3, height3, channel3;
	unsigned char *weather = stbi_load(path_weather, &width3, &height3, &channel3, 0);
	if ( weather == NULL )
	{
		printf("\ nCan't load weather_forecast \n");
		exit(1);
	}
	printf ("Weather-forecast Width = %d Height = %d Channel = %d\n", width3 , height3 , channel3 );
	
	
	
	processing_image(background, foreground, weather, width1, height1, 3, 4);
	stbi_write_png(save_path , width3 , height3 , channel3 , weather, width3 * channel3 );
	printf("Save image complete\n");
	return 0;
}
