package it.sevenbits.state_machine.formatter;


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
     * @param state  the state
     * @param string the string
     * @return the state
     */
    public State nextState(final State state, final String string) {
        return stateMap.getNextState(state, string);
    }

    /**
     * Gets start state from rep.
     *
     * @return the start state
     */
    public State getStartState() {
        return this.stateMap.getDefaultState();
    }
}
