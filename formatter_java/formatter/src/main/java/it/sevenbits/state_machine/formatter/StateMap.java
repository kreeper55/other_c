package it.sevenbits.state_machine.formatter;

import it.sevenbits.state_machine.state.Pair;
import it.sevenbits.state_machine.state.SetStates;
import it.sevenbits.state_machine.state.State;

import java.util.HashMap;
import java.util.Map;

/**
 * The type State map.
 */
public class StateMap {
    private final Map<Pair<State, String>, State> stateMap;
    private final State defaultState = SetStates.getDEFAULT();

    /**
     * Instantiates a new State map and map of states.
     */
    public StateMap() {
        stateMap = new HashMap<>();

        State word = SetStates.getWORD();
        State semicolon = SetStates.getSEMICOLON();
        State openBracket = SetStates.getOpenBracket();
        State closeBracket = SetStates.getCloseBracket();
        State onlySymbol = SetStates.getSYMBOL();
        State operation = SetStates.getOPERATION();

        stateMap.put(new Pair<>(word, SetStates.getWORD().getState()), word);
        stateMap.put(new Pair<>(word, SetStates.getSEMICOLON().getState()), semicolon);
        stateMap.put(new Pair<>(word, SetStates.getOpenBracket().getState()), openBracket);
        stateMap.put(new Pair<>(word, SetStates.getSYMBOL().getState()), onlySymbol);
        stateMap.put(new Pair<>(word, SetStates.getOPERATION().getState()), operation);

        stateMap.put(new Pair<>(semicolon, SetStates.getWORD().getState()), defaultState);
        stateMap.put(new Pair<>(semicolon, SetStates.getCloseBracket().getState()), closeBracket);
        stateMap.put(new Pair<>(semicolon, SetStates.getSEMICOLON().getState()), defaultState);
        stateMap.put(new Pair<>(semicolon, SetStates.getCOMMENT().getState()), defaultState);

        stateMap.put(new Pair<>(onlySymbol, SetStates.getOpenBracket().getState()), openBracket);
        stateMap.put(new Pair<>(onlySymbol, SetStates.getSEMICOLON().getState()), semicolon);
        stateMap.put(new Pair<>(onlySymbol, SetStates.getSYMBOL().getState()), onlySymbol);
        stateMap.put(new Pair<>(onlySymbol, SetStates.getCOMMENT().getState()), defaultState);

        stateMap.put(new Pair<>(openBracket, SetStates.getOpenBracket().getState()), openBracket);
        stateMap.put(new Pair<>(openBracket, SetStates.getCloseBracket().getState()), closeBracket);
        stateMap.put(new Pair<>(openBracket, SetStates.getWORD().getState()), word);
        stateMap.put(new Pair<>(closeBracket, SetStates.getCloseBracket().getState()), closeBracket);
        stateMap.put(new Pair<>(closeBracket, SetStates.getOpenBracket().getState()), openBracket);


        stateMap.put(new Pair<>(defaultState, SetStates.getCOMMENT().getState()), defaultState);
        stateMap.put(new Pair<>(defaultState, SetStates.getWORD().getState()), word);
        stateMap.put(new Pair<>(defaultState, SetStates.getSEMICOLON().getState()), semicolon);
        stateMap.put(new Pair<>(defaultState, SetStates.getCloseBracket().getState()), closeBracket);
        stateMap.put(new Pair<>(defaultState, SetStates.getOpenBracket().getState()), openBracket);
        stateMap.put(new Pair<>(defaultState, SetStates.getSYMBOL().getState()), onlySymbol);
        stateMap.put(new Pair<>(defaultState, SetStates.getOPERATION().getState()), operation);
        stateMap.put(new Pair<>(defaultState, SetStates.getTEXT().getState()), defaultState);

        stateMap.put(new Pair<>(operation, SetStates.getSEMICOLON().getState()), defaultState);
    }

    /**
     * Gets default state.
     *
     * @return the default state
     */
    public State getDefaultState() {
        return defaultState;
    }

    /**
     * Gets next state from repository.
     *
     * @param state  the state
     * @param string the string
     * @return the next state
     */
    public State getNextState(final State state, final String string) {
        return stateMap.getOrDefault(new Pair<>(state, string), defaultState);
    }
}
