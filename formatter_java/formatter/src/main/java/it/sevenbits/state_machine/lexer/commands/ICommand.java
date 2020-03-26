package it.sevenbits.state_machine.lexer.commands;

/**
 * The interface Command.
 */
public interface ICommand {
    /**
     * Execute command which call into command repository.
     *
     * @param symbol        the symbol
     * @param stringBuilder the string builder
     */
    void execute(Character symbol, StringBuilder stringBuilder);
}
