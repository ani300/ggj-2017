#include "StatesStack.h"

StatesStack::StatesStack(State::Context context)
: mStack()
, mPendingList()
, mContext(context)
, mFactories() {
}

void StatesStack::update(sf::Time dt) {
	// Iterate from top to bottom, stop as soon as update() returns false
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
		if (!(*itr)->update(dt))
			break;
	}

	applyPendingChanges();
}

void StatesStack::draw() {
	// Draw all active states from bottom to top
    for(State::Ptr& State : mStack) {
        State->draw();
    }
}

void StatesStack::handleEvent(const sf::Event& event) {
	// Iterate from top to bottom, stop as soon as handleEvent() returns false
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
		if (!(*itr)->handleEvent(event))
			break;
	}

	applyPendingChanges();
}

void StatesStack::pushState(StateType IDState) {
    mPendingList.push_back(PendingChange(Action::Push, IDState));
}

void StatesStack::popState() {
	mPendingList.push_back(PendingChange(Action::Pop));
}

void StatesStack::clearStates() {
	mPendingList.push_back(PendingChange(Action::Clear));
}

bool StatesStack::isEmpty() const {
	return mStack.empty();
}

State::Ptr StatesStack::createState(StateType IDState) {
    auto found = mFactories.find(IDState);
	assert(found != mFactories.end());

    return found->second();
}

void StatesStack::applyPendingChanges() {
    for (PendingChange change : mPendingList) {
        switch (change.mAction) {
            case Action::Push:
                mStack.push_back(createState(change.mStateID));
                break;

            case Action::Pop:
                mStack.pop_back();
                break;

            case Action::Clear:
                mStack.clear();
                break;
        }
    }

	mPendingList.clear();
}

StatesStack::PendingChange::PendingChange(Action action, StateType IDState)
: mAction(action)
, mStateID(IDState) {
}

void StatesStack::setContext(State::Context c) {
    mContext = c;
}
