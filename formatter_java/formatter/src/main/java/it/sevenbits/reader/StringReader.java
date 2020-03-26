package it.sevenbits.reader;

/**
 * The type String reader.
 */
public class StringReader implements IReader {
    private String str;
    private int position;

    /**
     * Instantiates a new String reader.
     *
     * @param str the str
     */
    public StringReader(final String str) {
        this.str = (str == null ? "" : str);
        this.position = 0;
    }

    @Override
    public boolean hasNext() {
        return position < str.length();
    }

    @Override
    public char read() throws ReaderException {
        if (hasNext()) {
            return str.charAt(position++);
        }
        throw new ReaderException("invalid character. out of string array");
    }
}
