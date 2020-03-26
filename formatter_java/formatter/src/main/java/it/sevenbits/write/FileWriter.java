package it.sevenbits.write;


import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.OutputStream;

/**
 * The type File writer.
 */
public class FileWriter implements IWriter, AutoCloseable {
    private static final Logger LOGGER = LoggerFactory.getLogger(FileWriter.class);
    private OutputStream os;

    /**
     * Instantiates a new File writer.
     *
     * @param path     the path
     * @param filename the filename
     * @throws FileNotFoundException the file not found exception
     */
    public FileWriter(final String path, final String filename) throws FileNotFoundException {
        File file = new File(path, filename);
        os = new FileOutputStream(file);
    }

    @Override
    public void write(final char symbol) throws WriterException {
        try {
            os.write(symbol);
        } catch (IOException e) {
            LOGGER.error("File Writer throw Exception\ncannot write symbol to file");
        }
    }

    @Override
    public void write(final String str) throws WriterException {
        try {
            os.write(str.getBytes());
        } catch (IOException e) {
            LOGGER.error("FileWriter throw Exception\nImpossible write string to file");
        }
    }

    @Override
    public void close() throws Exception {
        os.close();
        LOGGER.info("FileWriter(" + os.getClass().getName() + ") successfully closeable");
    }
}
