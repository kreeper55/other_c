package it.sevenbits.write;

/**
 * The type String writer.
 */
public class StringWriter implements IWriter {
    private StringBuilder stringBuilder;

    /**
     * Instantiates a new String writer.
     */
    public StringWriter() {
        stringBuilder = new StringBuilder();
    }

    @Override
    public void write(final char symbol) throws WriterException {
        stringBuilder.append(symbol);
    }

    @Override
    public void write(final String str) throws WriterException {
        stringBuilder.append(str);
    }

    /**
     *
     * @return String
     */
    public String toString() {
        return stringBuilder.toString();
    }
}
