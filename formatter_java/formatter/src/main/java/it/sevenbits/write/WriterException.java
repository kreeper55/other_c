package it.sevenbits.write;

/**
 * The type Writer exception.
 */
public class WriterException extends Exception {
    /**
     * Instantiates a new Writer exception.
     */
    public WriterException() {
    }

    /**
     * Instantiates a new Writer exception.
     *
     * @param message the message
     */
    public WriterException(final String message) {
        super(message);
    }

    /**
     * Instantiates a new Writer exception.
     *
     * @param message the message
     * @param cause   the cause
     */
    public WriterException(final String message, final Throwable cause) {
        super(message, cause);
    }

    /**
     * Instantiates a new Writer exception.
     *
     * @param cause the cause
     */
    public WriterException(final Throwable cause) {
        super(cause);
    }

    /**
     * Instantiates a new Writer exception.
     *
     * @param message            the message
     * @param cause              the cause
     * @param enableSuppression  the enable suppression
     * @param writableStackTrace the writable stack trace
     */
    public WriterException(final String message, final Throwable cause, final boolean enableSuppression, final boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }

}
