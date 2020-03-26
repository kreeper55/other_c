package it.sevenbits.write;

/**
 * The interface Writer.
 */
public interface IWriter {
    /**
     * Write.
     * write character to string
     *
     * @param symbol the symbol
     * @throws WriterException the writer exception
     */
    void write(char symbol) throws WriterException;

    /**
     * Write.
     *
     * @param str the str
     * @throws WriterException the writer exception
     */
    void write(String str) throws WriterException;
}
