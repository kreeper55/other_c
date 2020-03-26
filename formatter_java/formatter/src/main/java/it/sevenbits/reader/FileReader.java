package it.sevenbits.reader;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.IOException;
import java.io.File;
import java.io.InputStream;
import java.io.FileInputStream;

/**
 * The type File reader.
 */
public class FileReader implements IReader, AutoCloseable {
    private InputStream inputStream;
    private static final Logger LOGGER = LoggerFactory.getLogger(FileReader.class);

    /**
     * Instantiates a new File reader.
     *
     * @param path     the path
     * @param filename the filename
     * @throws IOException the io exception
     */
    public FileReader(final String path, final String filename) throws IOException {
        File file = new File(path, filename);
        inputStream = new FileInputStream(file);
    }

    @Override
    public boolean hasNext() {
        try {
            return (inputStream.available() > 0);
        } catch (IOException e) {
            LOGGER.error("Next elements isn't exists");
        }
        return false;
    }

    @Override
    public char read() throws ReaderException {
        if (hasNext()) {
            try {
                return ((char) inputStream.read());
            } catch (IOException e) {
                LOGGER.error("Reader cannot read next symbols! \nInput Output Exception");
            }
        }
        LOGGER.error("invalid character. out of bounds!");
        throw new ReaderException("Reader Exception! method read is failed");
    }

    @Override
    public void close() throws Exception {
        inputStream.close();
        LOGGER.info("file reader(" + inputStream.getClass().getName() + ") successfully closeable");
    }
}
