package it.sevenbits.state_machine.formatter.commands;

import it.sevenbits.lexer.IToken;
import it.sevenbits.write.IWriter;
import it.sevenbits.write.WriterException;

/**
 * The type Write space.
 */
public class WriteSpace implements ICommand {
    private static final char SPACE = ' ';

    @Override
    public void execute(final IToken token, final IWriter writer) {
        try {
            writer.write(SPACE);
        } catch (WriterException e) {
            e.printStackTrace();
        }
    }
}
