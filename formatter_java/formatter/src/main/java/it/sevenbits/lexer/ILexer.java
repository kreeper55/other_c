package it.sevenbits.lexer;

/**
 * The interface Lexer.
 */
public interface ILexer {
    /**
     * Has more tokens boolean.
     *
     * @return the boolean
     */
    boolean hasMoreTokens();

    /**
     * Read token token.
     *
     * @return the token
     * @throws LexerException the lexer exception
     */
    IToken readToken() throws LexerException;
}
