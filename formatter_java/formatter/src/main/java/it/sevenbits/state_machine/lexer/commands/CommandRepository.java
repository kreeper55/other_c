package it.sevenbits.state_machine.lexer.commands;

import it.sevenbits.state_machine.lexer.SetSymbols;
import it.sevenbits.state_machine.state.Pair;
import it.sevenbits.state_machine.state.SetStates;
import it.sevenbits.state_machine.state.State;

import java.util.HashMap;
import java.util.Map;

/**
 * The type Command repository.
 */
public final class CommandRepository {
    private static final Map<Pair<State, Character>, ICommand> COMMAND = setCommand();
    private static final ICommand IGNORE_COMMAND = new IgnoreCommand();

    private CommandRepository() {
    }

    private static HashMap<Pair<State, Character>, ICommand> setCommand() {
        //noinspection CheckStyle because it's faster (it's amount elements in map)
        HashMap<Pair<State, Character>, ICommand> commandMap = new HashMap<>(900);
        State aDefault = SetStates.getDEFAULT();
        State startState = SetStates.getSTART();
        State readLetterState = SetStates.getLETTER();
        State readSymbolState = SetStates.getSYMBOL();
        State readSymbolsState = SetStates.getSYMBOLS();
        State openBracket = SetStates.getOpenBracket();
        State closeBracket = SetStates.getCloseBracket();
        State semicolon = SetStates.getSEMICOLON();
        State comment = SetStates.getCOMMENT();   //  " // comment\n "
        State text = SetStates.getTEXT();         //  "something text"


        ICommand addToBufferCommand = new AddToBufferCommand();
        ICommand finishCommand = new FinishCommand();
        ICommand ignoreCommand = new IgnoreCommand();

        for (Character suspiciousSymbols : SetSymbols.getSuspiciousSymbols()) {
            commandMap.put(new Pair<>(startState, suspiciousSymbols), addToBufferCommand);
            commandMap.put(new Pair<>(aDefault, suspiciousSymbols), addToBufferCommand);
            commandMap.put(new Pair<>(readSymbolState, suspiciousSymbols), finishCommand);
            commandMap.put(new Pair<>(readLetterState, suspiciousSymbols), finishCommand);

            commandMap.put(new Pair<>(comment, suspiciousSymbols), addToBufferCommand);
            commandMap.put(new Pair<>(text, suspiciousSymbols), addToBufferCommand);
        }

        for (Character doubleSymbols : SetSymbols.getDoubleSymbols()) {
            commandMap.put(new Pair<>(readSymbolsState, doubleSymbols), addToBufferCommand);
            commandMap.put(new Pair<>(comment, doubleSymbols), addToBufferCommand);
            commandMap.put(new Pair<>(text, doubleSymbols), addToBufferCommand);
        }

        for (Character onlySymbol : SetSymbols.getOnlySymbols()) {
            commandMap.put(new Pair<>(startState, onlySymbol), addToBufferCommand);
            commandMap.put(new Pair<>(aDefault, onlySymbol), addToBufferCommand);
            commandMap.put(new Pair<>(readSymbolState, onlySymbol), finishCommand);
            commandMap.put(new Pair<>(readLetterState, onlySymbol), finishCommand);
            commandMap.put(new Pair<>(readSymbolsState, onlySymbol), finishCommand);

            commandMap.put(new Pair<>(comment, onlySymbol), addToBufferCommand);
            commandMap.put(new Pair<>(text, onlySymbol), addToBufferCommand);

            commandMap.put(new Pair<>(openBracket, onlySymbol), finishCommand);
            commandMap.put(new Pair<>(closeBracket, onlySymbol), finishCommand);
            commandMap.put(new Pair<>(semicolon, onlySymbol), finishCommand);
        }

        for (Character letter : SetSymbols.getAlphabetAndNumeric()) {
            commandMap.put(new Pair<>(startState, letter), addToBufferCommand);
            commandMap.put(new Pair<>(aDefault, letter), addToBufferCommand);
            commandMap.put(new Pair<>(readLetterState, letter), addToBufferCommand);
            commandMap.put(new Pair<>(readSymbolState, letter), finishCommand);
            commandMap.put(new Pair<>(readSymbolsState, letter), finishCommand);

            commandMap.put(new Pair<>(text, letter), addToBufferCommand);
            commandMap.put(new Pair<>(comment, letter), addToBufferCommand);

            commandMap.put(new Pair<>(openBracket, letter), finishCommand);
            commandMap.put(new Pair<>(closeBracket, letter), finishCommand);
            commandMap.put(new Pair<>(semicolon, letter), finishCommand);
        }

        for (Character ignoreSymbol : SetSymbols.getIgnoreSymbols()) {
            commandMap.put(new Pair<>(startState, ignoreSymbol), ignoreCommand);
            commandMap.put(new Pair<>(aDefault, ignoreSymbol), ignoreCommand);
            commandMap.put(new Pair<>(readLetterState, ignoreSymbol), finishCommand);
            commandMap.put(new Pair<>(readSymbolState, ignoreSymbol), finishCommand);
            commandMap.put(new Pair<>(readSymbolsState, ignoreSymbol), finishCommand);

            commandMap.put(new Pair<>(comment, ignoreSymbol), addToBufferCommand);
            commandMap.put(new Pair<>(text, ignoreSymbol), addToBufferCommand);
            commandMap.put(new Pair<>(openBracket, ignoreSymbol), finishCommand);
            commandMap.put(new Pair<>(closeBracket, ignoreSymbol), finishCommand);
            commandMap.put(new Pair<>(semicolon, ignoreSymbol), finishCommand);
        }

        for (Character operators : SetSymbols.getMainOperators()) {
            commandMap.put(new Pair<>(readSymbolState, operators), finishCommand);
            commandMap.put(new Pair<>(readSymbolsState, operators), finishCommand);
            commandMap.put(new Pair<>(readLetterState, operators), finishCommand);
            commandMap.put(new Pair<>(openBracket, operators), finishCommand);
            commandMap.put(new Pair<>(closeBracket, operators), finishCommand);
            commandMap.put(new Pair<>(semicolon, operators), finishCommand);
            commandMap.put(new Pair<>(comment, operators), addToBufferCommand);
            commandMap.put(new Pair<>(text, operators), addToBufferCommand);
        }

        commandMap.put(new Pair<>(startState, '{'), addToBufferCommand);
        commandMap.put(new Pair<>(startState, '}'), addToBufferCommand);
        commandMap.put(new Pair<>(startState, ';'), addToBufferCommand);

        commandMap.put(new Pair<>(aDefault, '{'), addToBufferCommand);
        commandMap.put(new Pair<>(aDefault, '}'), addToBufferCommand);
        commandMap.put(new Pair<>(aDefault, ';'), addToBufferCommand);


        commandMap.put(new Pair<>(startState, '\"'), addToBufferCommand);
        commandMap.put(new Pair<>(text, '\"'), addToBufferCommand);

        commandMap.put(new Pair<>(startState, '/'), addToBufferCommand);
        commandMap.put(new Pair<>(aDefault, '/'), addToBufferCommand);
        commandMap.put(new Pair<>(readSymbolsState, '/'), addToBufferCommand);
        commandMap.put(new Pair<>(openBracket, '/'), finishCommand);
        commandMap.put(new Pair<>(closeBracket, '/'), finishCommand);
        commandMap.put(new Pair<>(readSymbolState, '/'), finishCommand);
        commandMap.put(new Pair<>(comment, '\n'), finishCommand);
        commandMap.put(new Pair<>(comment, '\0'), finishCommand);

        return commandMap;
    }

    /**
     * Gets command from command.
     *
     * @param state  the state
     * @param symbol the symbol
     * @return the command
     */
    public static ICommand getCommand(final State state, final Character symbol) {
        return COMMAND.getOrDefault(new Pair<>(state, symbol), IGNORE_COMMAND);
    }
}
