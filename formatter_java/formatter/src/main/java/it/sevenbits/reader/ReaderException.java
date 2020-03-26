package it.sevenbits.reader;

/**
 * The type Reader exception.
 */
public class ReaderException extends Exception {
    /**
     * Instantiates a new Reader exception.
     */
    public ReaderException() {
    }

    /**
     * Instantiates a new Reader exception.
     *
     * @param message the message
     */
    public ReaderException(final String message) {
        super(message);
    }

    /**
     * Instantiates a new Reader exception.
     *
     * @param message the message
     * @param cause   the cause
     */
    public ReaderException(final String message, final Throwable cause) {
        super(message, cause);
    }

    /**
     * Instantiates a new Reader exception.
     *
     * @param cause the cause
     */
    public ReaderException(final Throwable cause) {
        super(cause);
    }

    /**
     * Instantiates a new Reader exception.
     *
     * @param message            the message
     * @param cause              the cause
     * @param enableSuppression  the enable suppression
     * @param writableStackTrace the writable stack trace
     */
    public ReaderException(final String message, final Throwable cause, final boolean enableSuppression, final boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
