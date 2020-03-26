package it.sevenbits;

import it.sevenbits.formatter.Formatter;
import it.sevenbits.formatter.FormatterException;
import it.sevenbits.lexer.ILexer;
import it.sevenbits.lexer.Lexer;
import it.sevenbits.lexer.LexerException;
import it.sevenbits.lexer.Token;
import it.sevenbits.reader.StringReader;
import it.sevenbits.write.IWriter;
import it.sevenbits.write.StringWriter;

import static org.junit.Assert.assertEquals;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

public class FormatterTest {

    @org.junit.Test
    public void validCode() throws FormatterException {
        String example = "aaa {bbb;ccc;}";
        StringWriter writer = new StringWriter();
        StringReader reader = new StringReader(example);
        ILexer lexer = new Lexer(reader);

        Formatter formatter = new Formatter(2);
        formatter.format(lexer, writer);
        String expected =   "aaa {\n" +
                            "  bbb;\n" +
                            "  ccc;\n" +
                            "}";
        assertEquals(expected, writer.toString());
    }

    @org.junit.Test
    public void checkIdentityLevel() throws FormatterException {
        String example = "{   {{  { }}  }    }  ";
        StringWriter writer = new StringWriter();
        StringReader reader = new StringReader(example);
        ILexer lexer = new Lexer(reader);

        Formatter formatter = new Formatter(4);
        formatter.format(lexer, writer);
        String expected =   "{\n" +
                            "    {\n" +
                            "        {\n" +
                            "            {\n" +
                            "            }\n" +
                            "        }\n" +
                            "    }\n" +
                            "}";
        assertEquals(expected, writer.toString());
    }

    @org.junit.Test
    public void validCodeClass() throws FormatterException {
        String example = "public class HelloWorld { System.out.println('Hello,World'); " +
                         "if    (str.charAt(i) == '') {    sb.append(); count++;} " +
                         "else if (str.charAt(i) == '') { sb.append(); " +
                         "if (str.charAt(i + 1) != '') { sb.append();}} else { System.out.println();}}";
        StringWriter writer = new StringWriter();
        StringReader reader = new StringReader(example);
        ILexer lexer = new Lexer(reader);

        Formatter formatter = new Formatter(4);
        formatter.format(lexer, writer);
        String expected =   "public class HelloWorld {\n" +
                            "    System.out.println('Hello,World');\n" +
                            "    if (str.charAt(i) == '') {\n" +
                            "        sb.append();\n" +
                            "        count++;\n" +
                            "    }\n" +
                            "    else if (str.charAt(i) == '') {\n" +
                            "        sb.append();\n" +
                            "        if (str.charAt(i + 1) != '') {\n" +
                            "            sb.append();\n" +
                            "        }\n" +
                            "    }\n" +
                            "    else {\n" +
                            "        System.out.println();\n" +
                            "    }\n" +
                            "}";
        assertEquals(expected, writer.toString());
    }

    @org.junit.Test
    public void operatorIf() throws FormatterException {
        String example = "if (i == 8) {}";
        StringWriter writer = new StringWriter();
        StringReader reader = new StringReader(example);
        ILexer lexer = new Lexer(reader);

        Formatter formatter = new Formatter(4);
        formatter.format(lexer, writer);
        String expected =   "if (i == 8) {\n" +
                            "}";
        assertEquals(expected, writer.toString());
    }

    @org.junit.Test
    public void codeFormatted() throws FormatterException {
        String example = "package it.sevenbits.write;\n" +
                         "public interface IWriter {\n" +
                         "    void write(char symbol) throws WriterException;\n" +
                         "    String getString();\n" +
                         "}";
        StringWriter writer = new StringWriter();
        StringReader reader = new StringReader(example);
        ILexer lexer = new Lexer(reader);

        Formatter formatter = new Formatter(4);
        formatter.format(lexer, writer);
        String expected =   "package it.sevenbits.write;\n" +
                            "public interface IWriter {\n" +
                            "    void write(char symbol) throws WriterException;\n" +
                            "    String getString();\n" +
                            "}";
        assertEquals(expected, writer.toString());
    }

    @org.junit.Test()
    public void FormatterWithoutLexer() throws FormatterException, LexerException {
        ILexer mockLexer = mock(ILexer.class);
        IWriter writer = new StringWriter();
        when(mockLexer.hasMoreTokens()).thenReturn(true, true, true, true, true, true, true, false);
        when(mockLexer.readToken()).thenReturn(new Token("aaa", "word"), new Token("{", "special"),
                new Token("bbb", "word"), new Token(";", "special"), new Token("ccc", "word"),
                new Token(";", "special"), new Token("}", "special"));


        Formatter formatter = new Formatter();
        formatter.format(mockLexer, writer);
        assertEquals("aaa {\n    bbb;\n    ccc;\n}", writer.toString());
    }
}