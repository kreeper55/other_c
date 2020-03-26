package it.sevenbits.state_machine.lexer;

import it.sevenbits.lexer.ILexer;
import it.sevenbits.lexer.IToken;
import it.sevenbits.lexer.LexerException;
import it.sevenbits.lexer.Token;
import it.sevenbits.state_machine.lexer.commands.CommandRepository;
import it.sevenbits.state_machine.lexer.commands.ICommand;
import it.sevenbits.reader.IReader;
import it.sevenbits.reader.ReaderException;
import it.sevenbits.state_machine.state.SetStates;
import it.sevenbits.state_machine.state.State;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.HashMap;
import java.util.Map;

/**
 * The type Lexer.
 */
public class LexerStateMachine implements ILexer {
    private static final Logger LOGGER = LoggerFactory.getLogger(LexerStateMachine.class);
    private Map<String, String> types;
    private IReader reader;
    private StateTransition stateTransition;
    private State currentState;
    private Character prevSymb;


    /**
     * Instantiates a new Lexer.
     *
     * @param reader the reader
     * @throws ReaderException the reader exception
     */
    public LexerStateMachine(final IReader reader) throws ReaderException {
        if (!reader.hasNext()) {
            LOGGER.error("IReader is empty\nImpossible read from reader");
            throw new ReaderException("IReader is empty");
        }

        this.reader = reader;
        this.stateTransition = new StateTransition();
        this.currentState = stateTransition.getStartState();
        this.prevSymb = null;

        types = new HashMap<>();
        types.put(SetStates.getOpenBracket().getState(), SetStates.getOpenBracket().getState());
        types.put(SetStates.getCloseBracket().getState(), SetStates.getCloseBracket().getState());
        types.put(SetStates.getSEMICOLON().getState(), SetStates.getSEMICOLON().getState());
        types.put(SetStates.getCOMMENT().getState(), SetStates.getCOMMENT().getState());
        types.put(SetStates.getSYMBOL().getState(), SetStates.getSYMBOL().getState());

        types.put(SetStates.getLETTER().getState(), SetStates.getWORD().getState());
        types.put(SetStates.getSYMBOLS().getState(), SetStates.getOPERATION().getState());
    }

    @Override
    public boolean hasMoreTokens() {
        return reader.hasNext() || prevSymb != null;
    }

    @Override
    public IToken readToken() throws LexerException {
        if (!reader.hasNext()) {
            if (prevSymb != null) {
                currentState = stateTransition.nextState(currentState, prevSymb);
                IToken token = new Token(prevSymb.toString(), types.get(currentState.getState()));
                LOGGER.info("token:  " + prevSymb + " \t\t " + currentState.getState());
                prevSymb = null;
                return token;
            }
            LOGGER.error("NO TOKEN");
            throw new LexerException("impossible to read next token");
        }

        Character currentSymbol = prevSymb;
        IToken token = new Token("NULL", "NULL");
        StringBuilder stringBuilder = new StringBuilder();

        final State startState = stateTransition.getStartState();
        final State finalState = stateTransition.getFinalState();
        State prevState;

        ICommand command;

        do {
            if (prevSymb == null) {
                try {
                    currentSymbol = reader.read();
                } catch (ReaderException e) {
                    LOGGER.error("ERROR READING");
                }
            }

            command = CommandRepository.getCommand(currentState, currentSymbol);
            command.execute(currentSymbol, stringBuilder);
            prevState = currentState;
            currentState = stateTransition.nextState(currentState, currentSymbol);

            if (currentState.equals(finalState)) {
                String type = types.get(prevState.getState());

                LOGGER.info("token:  " + stringBuilder.toString() + " \t\t " + type);
                token = new Token(stringBuilder.toString(), type);
                stringBuilder.setLength(0);
                currentState = stateTransition.getStartState();
                prevSymb = currentSymbol.equals(' ') ? null : currentSymbol;
            } else {
                prevSymb = null;
            }
        } while (!currentState.equals(startState) && hasMoreTokens());

        if (!reader.hasNext() && currentSymbol != null && token.getLexeme().equals("NULL")) {
            token = new Token(currentSymbol.toString(), types.get(currentState.getState()));
            LOGGER.info("token:  " + currentSymbol + " \t\t " + currentState.getState());
        }

        return token;
    }
}
