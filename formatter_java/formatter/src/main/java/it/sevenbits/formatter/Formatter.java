package it.sevenbits.formatter;

import it.sevenbits.lexer.ILexer;
import it.sevenbits.lexer.IToken;
import it.sevenbits.write.IWriter;
import it.sevenbits.lexer.LexerException;
import it.sevenbits.write.WriterException;

import java.util.Arrays;
import java.util.HashSet;

/**
 * The type Formatter.
 */
public class Formatter implements IFormatter {
    private static final String SEMICOLON = ";";
    private static final String OPENINGBRACE = "{";
    private static final String CLOSINGBRACE = "}";
    private static final String NEWLINE = "\n";
    private static final String SPACE = " ";
    private static final String DOT = ".";
    private int numberOfSpaces;

    private static final HashSet<String> RELATIONS = new HashSet<>(Arrays.asList(
            "?", "=",
            "+=", "-=", "/=", "*=", "%=", "«=", "»=", "&=", "^=", "|=",
            "=", "+=", "-=", "/=", "*=", "%=", "«=", "»=", "&=", "^=", "|=",
            "&&", "||", "!", "&", "|", "^", "~", "«", "»", "»>", "!=", "==",
            "<", "<=", ">", ">=", "+", "-", "*", "/", "%"
    ));

    /**
     * Instantiates a new Formatter.
     */
    @SuppressWarnings("checkstyle:MagicNumber")
    public Formatter() {
        //noinspection CheckStyle fixed numbers space
        numberOfSpaces = 4;
    }

    /**
     * Instantiates a new Formatter.
     *
     * @param spaces the spaces
     */
    public Formatter(final int spaces) {
        numberOfSpaces = spaces;
    }

    private void setSpaces(final IWriter writer, final int indentLevel, final int countSpaces) throws WriterException {
        for (int i = 0; i < indentLevel * countSpaces; i++) {
            writer.write(SPACE);
        }
    }

    @Override
    public void format(final ILexer lexer, final IWriter writer) throws FormatterException {
        boolean wasLine = false;
        boolean wasWord = false;
        boolean wasBrace = false;
        short indentLevel = 0;
        while (lexer.hasMoreTokens()) {
            try {
                IToken token = lexer.readToken();
                String type = token.getType();
                String lexeme = token.getLexeme();

                if (wasLine && (!lexeme.equals(NEWLINE))) {
                    if (lexeme.equals(CLOSINGBRACE)) {
                        --indentLevel;
                    }
                    writer.write(NEWLINE);
                    setSpaces(writer, indentLevel, numberOfSpaces);
                    wasLine = false;
                }

                switch (lexeme) {
                    case SEMICOLON:
                        writer.write(SEMICOLON);
                        wasLine = true;
                        wasWord = false;
                        wasBrace = false;
                        break;
                    case OPENINGBRACE:
                        if (wasBrace || wasWord) {
                            writer.write(SPACE);
                            wasBrace = false;
                        }
                        writer.write(OPENINGBRACE);
                        wasLine = true;
                        wasWord = false;
                        indentLevel++;
                        break;
                    case CLOSINGBRACE:
                        writer.write(CLOSINGBRACE);
                        wasLine = true;
                        wasWord = false;
                        wasBrace = false;
                        break;
                    case NEWLINE:
                        wasLine = true;
                        wasWord = false;
                        wasBrace = false;
                        break;
                    case DOT:
                        writer.write(DOT);
                        wasWord = false;
                        break;
                    default:
                        if (type.equals("word")) {
                            if (wasWord || lexeme.equals("throws")) {
                                writer.write(SPACE);
                            }
                            writer.write(lexeme);
                            if (lexeme.equals("if")) {
                                writer.write(SPACE);
                            }
                            wasWord = true;
                        } else {
                            if (lexeme.equals(")")) {
                                wasBrace = true;
                            }
                            if (RELATIONS.contains(lexeme)) {
                                writer.write(SPACE);
                                writer.write(lexeme);
                                writer.write(SPACE);
                            } else {
                                writer.write(lexeme);
                            }
                            wasWord = false;
                        }
                        break;
                }

            } catch (LexerException | WriterException e) {
                e.printStackTrace();
            }
        }
    }
}