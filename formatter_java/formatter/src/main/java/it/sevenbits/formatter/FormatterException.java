package it.sevenbits.formatter;

/**
 * The type Formatter exception.
 */
public class FormatterException extends Exception {
    /**
     * Instantiates a new Formatter exception.
     */
    public FormatterException() {
    }

    /**
     * Instantiates a new Formatter exception.
     *
     * @param message the message
     */
    public FormatterException(final String message) {
        super(message);
    }

    /**
     * Instantiates a new Formatter exception.
     *
     * @param message the message
     * @param cause   the cause
     */
    public FormatterException(final String message, final Throwable cause) {
        super(message, cause);
    }

    /**
     * Instantiates a new Formatter exception.
     *
     * @param cause the cause
     */
    public FormatterException(final Throwable cause) {
        super(cause);
    }

    /**
     * Instantiates a new Formatter exception.
     *
     * @param message            the message
     * @param cause              the cause
     * @param enableSuppression  the enable suppression
     * @param writableStackTrace the writable stack trace
     */
    public FormatterException(final String message, final Throwable cause,
                              final boolean enableSuppression, final boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
