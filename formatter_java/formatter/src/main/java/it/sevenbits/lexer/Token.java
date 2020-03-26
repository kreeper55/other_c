package it.sevenbits.lexer;

import java.util.Objects;

/**
 * The type Token.
 */
public class Token implements IToken {
    private String lexeme;
    private String type;

    /**
     * Instantiates a new Token.
     *
     * @param lexeme the lexeme
     * @param type   the type
     */
    public Token(final String lexeme, final String type) {
        this.lexeme = lexeme;
        this.type = type;
    }

    @Override
    public String getType() {
        return type;
    }

    @Override
    public String getLexeme() {
        return lexeme;
    }

    @Override
    public boolean equals(final Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        Token token = (Token) o;
        return lexeme.equals(token.lexeme) &&
                type.equals(token.type);
    }

    @Override
    public int hashCode() {
        return Objects.hash(lexeme, type);
    }
}
