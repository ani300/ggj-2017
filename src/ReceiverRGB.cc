#include "ReceiverRGB.h"
#include "WaveGenerator.h"

ReceiverRGB::ReceiverRGB(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators, sf::Color objective) : 
	Receiver(texture, generators),
	mObjective(objective)
{
	history_length = 120;
	activation_threshold = 1./history_length;

	activationHistory = std::vector<bool>(history_length, false);

	mSprite.setColor(objective);	
}


bool ReceiverRGB::isOnRightNow() {
	sf::Color totalInput(255/2,255/2,255/2,255);
	for(WaveGenerator* g : generators) {
		if(g->isPlaced()) {
			std::array<int, 4> genColor = static_cast<ColorGenerator*>(g)->colorAt(getWorldPosition());
			totalInput.r += genColor[0];
			totalInput.g += genColor[1];
			totalInput.b += genColor[2];
		}
	}
	
	int subr = int(totalInput.r) - int(mObjective.r);
	int subg = int(totalInput.g) - int(mObjective.g);
	int subb = int(totalInput.b) - int(mObjective.b);
	std::cout << subr << " " << subg << " " << subb << std::endl;
	return abs(subr) < 30 && abs(subg) < 30 && abs(subb) < 30;
}


void ReceiverRGB::updateCurrent(sf::Time dt) {
	on = isOn();
	if(on)
		setAnimation("On");
	else	
		setAnimation("Off");
	AnimationNode::updateCurrent(dt);
}
