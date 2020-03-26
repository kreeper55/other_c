package it.sevenbits.state_machine.formatter.commands;

import it.sevenbits.lexer.IToken;
import it.sevenbits.write.IWriter;

/**
 * The type Start.
 */
public class Start implements ICommand {
    @Override
    public void execute(final IToken token, final IWriter writer) {
        //  command start
    }
}
