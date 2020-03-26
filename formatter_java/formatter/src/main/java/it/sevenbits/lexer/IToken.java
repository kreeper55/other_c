package it.sevenbits.lexer;

/**
 * The interface Token.
 */
public interface IToken {
    /**
     * Gets type.
     *
     * @return the type
     */
    String getType();

    /**
     * Gets lexeme.
     *
     * @return the lexeme
     */
    String getLexeme();
}
