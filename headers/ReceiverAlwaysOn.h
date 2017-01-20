#ifndef RECEIVER_ALWAYS_ON_H
#define RECEIVER_ALWAYS_ON_H

#include "Receiver.h"
/*
* Receiver always on
* This receiver is on when has been above 0 during the last 60 frames
*/
class ReceiverAlwaysOn: public Receiver{
	public:
		ReceiverAlwaysOn(const sf::Texture& texture, std::vector<WaveGenerator>* generators);

	private:
		const int HISTORY_LENGTH;
		const float ACTIVATION_THRESHOLD;

		bool isOn();
		bool isOnRightNow();
		void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt) override;

#endif //RECEIVER_H
