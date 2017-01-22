#include "LinkedReceiver.h"

LinkedReceiver::LinkedReceiver(std::vector<Receiver*> const& r,
	std::vector<WaveGenerator*> const& g){
	receivers = r;
	generators = g;
}

LinkedReceiver::getState(){
	for(auto const& r: receivers)
	{
		r.isOn();
	}
}
