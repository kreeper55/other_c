package it.sevenbits.state_machine.lexer;

import it.sevenbits.state_machine.state.State;

/**
 * The type State transition.
 */
public class StateTransition {

    private final StateMap stateMap;

    /**
     * Instantiates a new State transition.
     */
    public StateTransition() {
        this.stateMap = new StateMap();
    }

    /**
     * Next state state.
     *
     * @param state     the state
     * @param character the character
     * @return the state
     */
    public State nextState(final State state, final Character character) {
        return stateMap.getNextState(state, character);
    }

    /**
     * Gets start state.
     *
     * @return the start state
     */
    public State getStartState() {
        return StateMap.getStartState();
    }

    /**
     * Gets final state.
     *
     * @return the final state
     */
    public State getFinalState() {
        return StateMap.getFinalState();
    }
}
