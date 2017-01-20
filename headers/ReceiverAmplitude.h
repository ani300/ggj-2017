#ifndef RECEIVER_AMPLITUDE_H
#define RECEIVER_AMPLITUDE_H

#include "Receiver.h"
/*
* Receiver amplitude
* This receiver is on when a target amplitude has been reached in 
* the last ACTIVATION_THRESHOLD frames
*/
class ReceiverAmplitude: public Receiver{
	public:
		ReceiverAmplitude(const sf::Texture& texture, std::vector<WaveGenerator>* generators, float target);

	private:
		const int HISTORY_LENGTH;
		const float ACTIVATION_THRESHOLD;
		float target;

		bool isOn();
		bool isOnRightNow();
		void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt) override;

#endif //RECEIVER_AMPLITUDE_H