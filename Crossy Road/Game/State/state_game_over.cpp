#include"state_game_over.h"
game_over::game_over(Game& game)
	: state_base(game)
	, m_gameover_menu(game.get_window(), 450)
{
	label.setFillColor(sf::Color::White);
	label.setCharacterSize(50);
	label.setOutlineColor(sf::Color::Black);
	label.setOutlineThickness(2);
	label.setPosition({ 520,190 });

	m_score.setFillColor(sf::Color::Blue);
	m_score.setOutlineColor(sf::Color::Yellow);
	m_score.setOutlineThickness(2);
	m_score.setPosition({ 470,290 });
	m_score.setCharacterSize(40);
	

	m_highscore.setFillColor(sf::Color::Red);
	m_highscore.setOutlineColor(sf::Color::Yellow);
	m_highscore.setOutlineThickness(2);
	m_highscore.setPosition({ 470,245 });
	m_highscore.setCharacterSize(42);

	container.setPosition({ 450,195 });
	container.setSize({ 400,300 });
	container.setTexture(&asset::texture().get("blue_panel", "png"));

	auto ExitGameBtn = makeButton();
	ExitGameBtn->setText("Exit Game");
	ExitGameBtn->setFunction([&]() {
		m_exit = true;
		});

	m_gameover_menu.addWidget(std::move(ExitGameBtn));
	m_gameover_menu.setTitle("", game.get_window());
	
}
bool game_over::GetState()
{
	return m_exit;
}
void game_over::draw(sf::RenderTarget& target) {
	
	target.draw(container);
	m_gameover_menu.render(target);
	target.draw(label);
	target.draw(m_score);
	target.draw(m_highscore);
}
void game_over::handleEvent(sf::Event e) {
	m_gameover_menu.handleEvent(e, game().get_window());

}
void game_over::update(sf::Time dental_time) {
	
}
void game_over::updateScore(int _score) {
	score = _score;
	if (score > highscore)
	{
		highscore = score;
		m_highscore.setString(NewHighScore_label + "	" + std::to_string(highscore));
	}
	else {
		m_highscore.setString(HighScore_label + "	" + std::to_string(highscore));
		m_score.setString(Score_label + "	" + std::to_string(score));
	}
	
	label.setString("GAME	OVER");
}