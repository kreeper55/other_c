package it.sevenbits.reader;

/**
 * The interface Reader.
 */
public interface IReader {
    /**
     * Has next boolean.
     * checks next element
     * @return the boolean
     */
    boolean hasNext();

    /**
     * Read char.
     * reads next element
     * @return the char
     * @throws ReaderException the reader exception
     */
    char read() throws ReaderException;
}
