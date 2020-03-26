package it.sevenbits.state_machine.formatter.commands;

import it.sevenbits.lexer.IToken;
import it.sevenbits.write.IWriter;
import it.sevenbits.write.WriterException;

/**
 * The type Write indent.
 */
public class WriteIndent implements ICommand {
    private int indent;
    private int numberOfSpaces;
    private boolean wasLine;

    /**
     * Instantiates a new Write indent.
     */
    public WriteIndent() {
        this.indent = 0;
        this.numberOfSpaces = 4;
    }

    @Override
    public void execute(final IToken token, final IWriter writer) {
        if (wasLine) {
            if (token.getType().equals("CLOSE_BRACKET")) {
                indent--;
            }
            wasLine = false;
        }

        for (int i = 0; i < indent * numberOfSpaces; i++) {
            try {
                writer.write(' ');
            } catch (WriterException e) {
                e.printStackTrace();
            }
        }
        wasLine = true;

        if (token.getType().equals("OPEN_BRACKET")) {
            indent++;
        }
    }
}
