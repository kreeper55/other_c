package it.sevenbits.state_machine.formatter.commands;

import it.sevenbits.lexer.IToken;
import it.sevenbits.write.IWriter;

/**
 * The interface Command.
 */
public interface ICommand {
    /**
     * Execute command which call from command repository.
     *
     * @param token  the token
     * @param writer the writer
     */
    void execute(IToken token, IWriter writer);
}
