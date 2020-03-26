package it.sevenbits.state_machine.lexer.commands;

/**
 * The type Add to buffer command.
 */
public class AddToBufferCommand implements ICommand {

    @Override
    public void execute(final Character symbol, final StringBuilder stringBuilder) {
        stringBuilder.append(symbol);
    }
}
