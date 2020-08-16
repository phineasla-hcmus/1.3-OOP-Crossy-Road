#ifndef _resource_storage
#define _resource_storage
//Singleton pattern
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"res_manager.h"
#include"../Util/no_copy.h"
//Hold all resources, using singleton pattern
class resource : public no_copy
{
private:
	resource();
	res_manager<sf::Font>			fonts;			//fonts
	res_manager<sf::Texture>		textures;		//textures
	res_manager<sf::SoundBuffer>	sound_buffers;	//sounds
public:
	static resource& get();
	//resource
};
#endif // !_resource_storage
