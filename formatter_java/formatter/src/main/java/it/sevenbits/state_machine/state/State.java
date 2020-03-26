package it.sevenbits.state_machine.state;

import java.util.Objects;


/**
 * The type State.
 */
public class State {
    private final String state;

    /**
     * Instantiates a new State.
     *
     * @param state the state
     */
    public State(final String state) {
        this.state = state;
    }

    /**
     * Gets state.
     *
     * @return the state
     */
    public String getState() {
        return state;
    }

    @Override
    public boolean equals(final Object o) {
        if (this == o)  {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        State state1 = (State) o;
        return Objects.equals(state, state1.state);
    }

    @Override
    public int hashCode() {
        return Objects.hash(state);
    }
}
