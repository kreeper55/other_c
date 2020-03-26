package it.sevenbits.state_machine.lexer;

import it.sevenbits.state_machine.state.Pair;
import it.sevenbits.state_machine.state.SetStates;
import it.sevenbits.state_machine.state.State;

import java.util.HashMap;
import java.util.Map;

/**
 * The type State map.
 */
class StateMap {
    private static final State START_STATE = SetStates.getSTART();
    private static final State FINAL_STATE = SetStates.getFINAL();

    private final Map<Pair<State, Character>, State> states;

    /**
     * Instantiates a new State map.
     */
    @SuppressWarnings("checkstyle:MagicNumber")
    StateMap() {
        //noinspection CheckStyle, it's fast (in map added 560 elements)
        states = new HashMap<>(900);
        State aDefault = SetStates.getDEFAULT();
        State readLetterState = SetStates.getLETTER();
        State readSymbolState = SetStates.getSYMBOL();
        State readSymbolsState = SetStates.getSYMBOLS();
        State openBracket = SetStates.getOpenBracket();
        State closeBracket = SetStates.getCloseBracket();
        State semicolon = SetStates.getSEMICOLON();
        State comment = SetStates.getCOMMENT();
        State text = SetStates.getTEXT();

        for (Character suspiciousSymbol : SetSymbols.getSuspiciousSymbols()) {
            states.put(new Pair<>(START_STATE, suspiciousSymbol), readSymbolsState);
            states.put(new Pair<>(aDefault, suspiciousSymbol), readSymbolsState);
            states.put(new Pair<>(readSymbolState, suspiciousSymbol), FINAL_STATE);
            states.put(new Pair<>(readLetterState, suspiciousSymbol), FINAL_STATE);
            states.put(new Pair<>(readSymbolsState, suspiciousSymbol), FINAL_STATE);

            states.put(new Pair<>(text, suspiciousSymbol), text);
            states.put(new Pair<>(comment, suspiciousSymbol), comment);
        }

        for (Character onlySymbol : SetSymbols.getOnlySymbols()) {
            states.put(new Pair<>(START_STATE, onlySymbol), readSymbolState);
            states.put(new Pair<>(aDefault, onlySymbol), readSymbolState);
            states.put(new Pair<>(readLetterState, onlySymbol), FINAL_STATE);
            states.put(new Pair<>(readSymbolState, onlySymbol), FINAL_STATE);
            states.put(new Pair<>(readSymbolsState, onlySymbol), FINAL_STATE);

            states.put(new Pair<>(text, onlySymbol), text);
            states.put(new Pair<>(comment, onlySymbol), comment);

            states.put(new Pair<>(openBracket, onlySymbol), FINAL_STATE);
            states.put(new Pair<>(closeBracket, onlySymbol), FINAL_STATE);
            states.put(new Pair<>(semicolon, onlySymbol), FINAL_STATE);
        }

        for (Character doubleSymbols : SetSymbols.getDoubleSymbols()) {
            states.put(new Pair<>(readSymbolsState, doubleSymbols), readSymbolsState);
            states.put(new Pair<>(text, doubleSymbols), text);
            states.put(new Pair<>(comment, doubleSymbols), comment);
        }

        for (Character letter : SetSymbols.getAlphabetAndNumeric()) {
            states.put(new Pair<>(START_STATE, letter), readLetterState);
            states.put(new Pair<>(aDefault, letter), readLetterState);
            states.put(new Pair<>(readLetterState, letter), readLetterState);
            states.put(new Pair<>(readSymbolState, letter), FINAL_STATE);
            states.put(new Pair<>(readSymbolsState, letter), FINAL_STATE);

            states.put(new Pair<>(text, letter), text);
            states.put(new Pair<>(comment, letter), comment);

            states.put(new Pair<>(openBracket, letter), FINAL_STATE);
            states.put(new Pair<>(closeBracket, letter), FINAL_STATE);
            states.put(new Pair<>(semicolon, letter), FINAL_STATE);
        }

        for (Character ignoreSymbols : SetSymbols.getIgnoreSymbols()) {
            states.put(new Pair<>(START_STATE, ignoreSymbols), aDefault);
            states.put(new Pair<>(aDefault, ignoreSymbols), aDefault);
            states.put(new Pair<>(readLetterState, ignoreSymbols), FINAL_STATE);
            states.put(new Pair<>(readSymbolState, ignoreSymbols), FINAL_STATE);
            states.put(new Pair<>(readSymbolsState, ignoreSymbols), FINAL_STATE);

            states.put(new Pair<>(comment, ignoreSymbols), comment);
            states.put(new Pair<>(text, ignoreSymbols), text);

            states.put(new Pair<>(openBracket, ignoreSymbols), FINAL_STATE);
            states.put(new Pair<>(closeBracket, ignoreSymbols), FINAL_STATE);
            states.put(new Pair<>(semicolon, ignoreSymbols), FINAL_STATE);
        }

        for (Character operators: SetSymbols.getMainOperators()) {
            states.put(new Pair<>(readSymbolState, operators), FINAL_STATE);
            states.put(new Pair<>(readSymbolsState, operators), FINAL_STATE);
            states.put(new Pair<>(readLetterState, operators), FINAL_STATE);
            states.put(new Pair<>(openBracket, operators), FINAL_STATE);
            states.put(new Pair<>(closeBracket, operators), FINAL_STATE);
            states.put(new Pair<>(semicolon, operators), FINAL_STATE);
            states.put(new Pair<>(comment, operators), comment);
            states.put(new Pair<>(text, operators), text);
        }

        states.put(new Pair<>(START_STATE, '{'), openBracket);
        states.put(new Pair<>(START_STATE, '}'), closeBracket);
        states.put(new Pair<>(START_STATE, ';'), semicolon);

        states.put(new Pair<>(aDefault, '{'), openBracket);
        states.put(new Pair<>(aDefault, '}'), closeBracket);
        states.put(new Pair<>(aDefault, ';'), semicolon);

        states.put(new Pair<>(START_STATE, '\"'), text);
        states.put(new Pair<>(readLetterState, '\"'), FINAL_STATE);
        states.put(new Pair<>(readSymbolState, '\"'), FINAL_STATE);
        states.put(new Pair<>(readSymbolsState, '\"'), FINAL_STATE);
        states.put(new Pair<>(text, '\"'), readSymbolState);

        states.put(new Pair<>(START_STATE, '/'), readSymbolsState);
        states.put(new Pair<>(aDefault, '/'), readSymbolsState);
        states.put(new Pair<>(readSymbolsState, '/'), comment);
        states.put(new Pair<>(openBracket, '/'), FINAL_STATE);
        states.put(new Pair<>(closeBracket, '/'), FINAL_STATE);
        states.put(new Pair<>(readSymbolState, '/'), FINAL_STATE);
        states.put(new Pair<>(semicolon, '/'), FINAL_STATE);
        states.put(new Pair<>(comment, '\n'), FINAL_STATE);
        states.put(new Pair<>(comment, '\0'), FINAL_STATE);
    }

    /**
     * Gets start state.
     *
     * @return the start state
     */
    public static State getStartState() {
        return START_STATE;
    }

    /**
     * Gets final state.
     *
     * @return the final state
     */
    public static State getFinalState() {
        return FINAL_STATE;
    }

    /**
     * Gets next state.
     *
     * @param state     the state
     * @param character the character
     * @return the next state
     */
    public State getNextState(final State state, final Character character) {
        return states.getOrDefault(new Pair<>(state, character), START_STATE);
    }
}