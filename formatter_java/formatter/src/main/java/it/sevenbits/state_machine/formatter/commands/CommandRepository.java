package it.sevenbits.state_machine.formatter.commands;

import it.sevenbits.state_machine.state.Pair;
import it.sevenbits.state_machine.state.SetStates;
import it.sevenbits.state_machine.state.State;

import java.util.List;
import java.util.LinkedList;
import java.util.Map;
import java.util.HashMap;
import java.util.Collections;
import java.util.Arrays;

/**
 * The type Command repository.
 */
public final class CommandRepository {
    @SuppressWarnings("checkstyle:ConstantName")
    private static final Map<Pair<State, String>, List<ICommand>> COMMANDS = setCommands();
    private static final ICommand START = new Start();
    private static final List<ICommand> START_COMMAND_LIST = new LinkedList<>(Collections.singletonList(START));

    private CommandRepository() {
    }

    private static Map<Pair<State, String>, List<ICommand>> setCommands() {
        Map<Pair<State, String>, List<ICommand>> commands = new HashMap<>();
        ICommand writeToken = new WriteToken();
        ICommand writeNewLine = new WriteNewLine();
        ICommand writeIndent = new WriteIndent();
        ICommand writeSpace = new WriteSpace();

        State defaultState = SetStates.getDEFAULT();
        State word = SetStates.getWORD();
        State semicolon = SetStates.getSEMICOLON();
        State openBracket = SetStates.getOpenBracket();
        State closeBracket = SetStates.getCloseBracket();
        State onlySymbol = SetStates.getSYMBOL();
        State operation = SetStates.getOPERATION();

        List<ICommand> defaultCommandsList = new LinkedList<>(Collections.singletonList(writeToken));
        List<ICommand> indentWordCommandList = new LinkedList<>(Arrays.asList(writeIndent, writeToken));
        List<ICommand> newlineWordCommandList = new LinkedList<>(Arrays.asList(writeNewLine, writeIndent, writeToken));
        List<ICommand> spaceWordCommandList = new LinkedList<>(Arrays.asList(writeSpace, writeToken));

        List<ICommand> operationCommandList = new LinkedList<>(Arrays.asList(writeSpace, writeToken, writeSpace));

        List<ICommand> openBracketCommandList = new LinkedList<>(Arrays.asList(writeSpace, writeToken, writeNewLine, writeIndent));
        List<ICommand> closeBracketCommandList = new LinkedList<>(Arrays.asList(writeSpace, writeNewLine, writeIndent, writeToken));
        List<ICommand> bracketCommandList = new LinkedList<>(Arrays.asList(writeIndent, writeToken, writeNewLine));
        List<ICommand> commentCommandList = new LinkedList<>(Arrays.asList(writeToken, writeNewLine, writeIndent));

        commands.put(new Pair<>(word, SetStates.getWORD().getState()), spaceWordCommandList);
        commands.put(new Pair<>(word, SetStates.getSEMICOLON().getState()), defaultCommandsList);
        commands.put(new Pair<>(word, SetStates.getOpenBracket().getState()), openBracketCommandList);
        commands.put(new Pair<>(word, SetStates.getSYMBOL().getState()), defaultCommandsList);
        commands.put(new Pair<>(word, SetStates.getOPERATION().getState()), operationCommandList);

        commands.put(new Pair<>(semicolon, SetStates.getWORD().getState()), newlineWordCommandList);
        commands.put(new Pair<>(semicolon, SetStates.getCloseBracket().getState()), closeBracketCommandList);
        commands.put(new Pair<>(semicolon, SetStates.getCOMMENT().getState()), commentCommandList);

        commands.put(new Pair<>(operation, SetStates.getWORD().getState()), defaultCommandsList);
        commands.put(new Pair<>(operation, SetStates.getSYMBOL().getState()), defaultCommandsList);
        commands.put(new Pair<>(operation, SetStates.getSEMICOLON().getState()), defaultCommandsList);

        commands.put(new Pair<>(onlySymbol, SetStates.getWORD().getState()), defaultCommandsList);
        commands.put(new Pair<>(onlySymbol, SetStates.getOpenBracket().getState()), bracketCommandList);
        commands.put(new Pair<>(onlySymbol, SetStates.getOPERATION().getState()), operationCommandList);
        commands.put(new Pair<>(onlySymbol, SetStates.getSYMBOL().getState()), defaultCommandsList);
        commands.put(new Pair<>(onlySymbol, SetStates.getSEMICOLON().getState()), defaultCommandsList);
        commands.put(new Pair<>(onlySymbol, SetStates.getCOMMENT().getState()), commentCommandList);
        commands.put(new Pair<>(onlySymbol, SetStates.getTEXT().getState()), defaultCommandsList);

        commands.put(new Pair<>(openBracket, SetStates.getWORD().getState()), indentWordCommandList);
        commands.put(new Pair<>(openBracket, SetStates.getOpenBracket().getState()), bracketCommandList);
        commands.put(new Pair<>(openBracket, SetStates.getCloseBracket().getState()), bracketCommandList);
        commands.put(new Pair<>(openBracket, SetStates.getTEXT().getState()), defaultCommandsList);
        commands.put(new Pair<>(openBracket, SetStates.getCOMMENT().getState()), commentCommandList);

        commands.put(new Pair<>(closeBracket, SetStates.getCloseBracket().getState()), bracketCommandList);
        commands.put(new Pair<>(closeBracket, SetStates.getWORD().getState()), spaceWordCommandList);

        commands.put(new Pair<>(defaultState, SetStates.getWORD().getState()), defaultCommandsList);
        commands.put(new Pair<>(defaultState, SetStates.getOpenBracket().getState()), bracketCommandList);
        commands.put(new Pair<>(defaultState, SetStates.getCloseBracket().getState()), bracketCommandList);
        commands.put(new Pair<>(defaultState, SetStates.getSEMICOLON().getState()), defaultCommandsList);
        commands.put(new Pair<>(defaultState, SetStates.getSYMBOL().getState()), defaultCommandsList);
        commands.put(new Pair<>(defaultState, SetStates.getOPERATION().getState()), operationCommandList);

        commands.put(new Pair<>(defaultState, SetStates.getCOMMENT().getState()), defaultCommandsList);
        commands.put(new Pair<>(closeBracket, SetStates.getCOMMENT().getState()), openBracketCommandList);


        return commands;
    }

    /**
     * Gets next command from repository.
     *
     * @param state  the state
     * @param string the string
     * @return the next command
     */
    public static List<ICommand> getNextCommand(final State state, final String string) {
        return COMMANDS.getOrDefault(new Pair<>(state, string), START_COMMAND_LIST);
    }
}
