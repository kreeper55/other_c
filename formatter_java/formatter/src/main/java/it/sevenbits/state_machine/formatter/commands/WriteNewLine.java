package it.sevenbits.state_machine.formatter.commands;

import it.sevenbits.lexer.IToken;
import it.sevenbits.write.IWriter;
import it.sevenbits.write.WriterException;

/**
 * The type Write new line.
 */
public class WriteNewLine implements ICommand {
    private static final char NEWLINE = '\n';

    @Override
    public void execute(final IToken token, final IWriter writer) {
        try {
            writer.write(NEWLINE);
        } catch (WriterException e) {
            e.printStackTrace();
        }

    }
}
