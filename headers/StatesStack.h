#pragma once

#include "State.h"
#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"
#include "Utils.h"

class StatesStack : private sf::NonCopyable {
	public:
		enum class Action {
			Push,
			Pop,
			Clear,
			SetLevel
		};

		explicit StatesStack(State::Context context);

		template <typename T>
			void registerState(StateType IDState);

		bool isEmpty() const;

		void draw();
		void update(sf::Time dt);
		void handleEvent(const sf::Event& event);

		void popState();
		void clearStates();
		void pushState(StateType IDState);
		void setLevel(Levels level);

		void setContext(State::Context c);

	private:
		StateType readNextState();

		State::Ptr createState(StateType IDState);
		void applyPendingChanges();

		struct PendingChange {
			explicit PendingChange(Action action, StateType stateID = StateType::None);
			explicit PendingChange(Action action, Levels level);

			Action mAction;
			StateType mStateID;
			Levels level;
		};

		std::vector<State::Ptr>	mStack;
		std::vector<PendingChange> mPendingList;

		State::Context mContext;
		std::map<StateType, std::function<State::Ptr()>> mFactories;
};


template <typename T>
void StatesStack::registerState(StateType IDState) {
	mFactories[IDState] = [this] () {
		return State::Ptr(new T(*this, mContext));
	};
}
