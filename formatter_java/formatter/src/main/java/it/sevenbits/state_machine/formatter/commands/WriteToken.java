package it.sevenbits.state_machine.formatter.commands;

import it.sevenbits.lexer.IToken;
import it.sevenbits.write.IWriter;
import it.sevenbits.write.WriterException;

/**
 * The type Write token.
 */
public class WriteToken implements ICommand {
    @Override
    public void execute(final IToken token, final IWriter writer) {
        try {
            writer.write(token.getLexeme());
        } catch (WriterException e) {
            e.printStackTrace();
        }
    }
}
