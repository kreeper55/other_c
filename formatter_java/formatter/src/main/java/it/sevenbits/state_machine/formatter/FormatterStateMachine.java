package it.sevenbits.state_machine.formatter;

import it.sevenbits.formatter.FormatterException;
import it.sevenbits.formatter.IFormatter;
import it.sevenbits.lexer.ILexer;
import it.sevenbits.lexer.IToken;
import it.sevenbits.state_machine.formatter.commands.CommandRepository;
import it.sevenbits.state_machine.formatter.commands.ICommand;
import it.sevenbits.state_machine.state.SetStates;
import it.sevenbits.state_machine.state.State;
import it.sevenbits.write.IWriter;
import it.sevenbits.lexer.LexerException;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.LinkedList;
import java.util.List;

/**
 * The type Formatter.
 */
public class FormatterStateMachine implements IFormatter {

    /**
     * Instantiates a new Formatter state machine.
     */
    public FormatterStateMachine() {
    }

    private final Logger logger = LoggerFactory.getLogger(FormatterStateMachine.class);

    @Override
    public void format(final ILexer lexer, final IWriter writer) throws FormatterException {
        List<ICommand> commandsList = new LinkedList<>();

        String typeLexeme = "";

        StateTransition stateTransition = new StateTransition();
        State currentState = stateTransition.getStartState();
        IToken currentToken = null;

        do {
            try {
                currentToken = lexer.readToken();
                if (currentToken.getLexeme().equals("z")) {
                    int c = 0;
                }
            } catch (LexerException e) {
                logger.error("NEXT TOKEN DOESN'T EXIST");
            }

            if (currentToken != null) {
                typeLexeme = currentToken.getType();
            } else {
                typeLexeme = SetStates.getSYMBOL().getState();
            }
            commandsList.addAll(CommandRepository.getNextCommand(currentState, typeLexeme));
            for (ICommand command : commandsList) {
                command.execute(currentToken, writer);
            }
            commandsList.clear();

            currentState = stateTransition.nextState(currentState, typeLexeme);
        } while (lexer.hasMoreTokens());


        logger.info("Formatter successfully composition tokens in one string");
    }
}