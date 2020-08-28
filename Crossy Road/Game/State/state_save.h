#ifndef _STATE_SAVE_H
#define _STATE_SAVE_H
#include"state_load.h"
#include"../SaveLevel.h"
#include"../../PCH.h"
constexpr auto SAVE_FILE_NAME = "D:\\";  //need Phuc redefine the link
class state_save :public state_base {
private:
	StackMenu save_menu;
	SaveInf m_save;
	std::string m_name;
public:
	state_save(Game&, SaveInf& _save);
	void handleEvent(sf::Event e)			override;
	void update(sf::Time delta_time)		override;
	void draw(sf::RenderTarget& renderer)	override;
	//void WritetoFile(std::string name);
};
#endif // !_STATE_SAVE_H