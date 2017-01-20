#ifndef RECEIVER_ALWAYS_OFF_H
#define RECEIVER_ALWAYS_OFF_H

#include "Receiver.h"
/*
* Receiver always off
* This receiver is on when has been blow 0 during the last 60 frames
*/
class ReceiverAlwaysOff: public Receiver{
	public:
		ReceiverAlwaysOff(const sf::Texture& texture);
		
	private:
		const int HISTORY_LENGTH;
		const float ACTIVATION_THRESHOLD;

		bool isOn();
		bool isOnRightNow();
		void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt) override;

#endif //RECEIVER_ALWAYS_OFF_H