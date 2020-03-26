package it.sevenbits.formatter;

import it.sevenbits.lexer.ILexer;
import it.sevenbits.write.IWriter;

/**
 * The interface Formatter.
 */
public interface IFormatter {
    /**
     * Format.
     *
     * @param lexer the lexer
     * @param writer the writer
     * @throws FormatterException the formatter exception
     */
    void format(final ILexer lexer, final IWriter writer) throws FormatterException;
}
