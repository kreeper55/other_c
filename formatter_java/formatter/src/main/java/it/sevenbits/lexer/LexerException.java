package it.sevenbits.lexer;

/**
 * The type Lexer exception.
 */
public class LexerException extends Exception {
    /**
     * Instantiates a new Lexer exception.
     */
    public LexerException() {
    }

    /**
     * Instantiates a new Lexer exception.
     *
     * @param message the message
     */
    public LexerException(final String message) {
        super(message);
    }

    /**
     * Instantiates a new Lexer exception.
     *
     * @param message the message
     * @param cause   the cause
     */
    public LexerException(final String message, final Throwable cause) {
        super(message, cause);
    }

    /**
     * Instantiates a new Lexer exception.
     *
     * @param cause the cause
     */
    public LexerException(final Throwable cause) {
        super(cause);
    }

    /**
     * Instantiates a new Lexer exception.
     *
     * @param message            the message
     * @param cause              the cause
     * @param enableSuppression  the enable suppression
     * @param writableStackTrace the writable stack trace
     */
    public LexerException(final String message, final Throwable cause, final boolean enableSuppression, final boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
