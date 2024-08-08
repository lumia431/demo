using System.Collections;
using System.Text;

static Dictionary<string, string> GetDatabases()
{
    #region 读取TNS文件
    string output = "";
    string fileLine;
    Stack parens = new Stack();
    Dictionary<string, string> keyValues = new Dictionary<string, string>();
    StringBuilder stringBuilder = new StringBuilder();
    // open tnsnames.ora 
    StreamReader sr;
    try
    {
        sr = new StreamReader(@"tnsnames.ora");
    }
    catch (System.IO.FileNotFoundException ex)
    {
        throw ex;
    }
    #endregion
    // 读取文件的第一行
    fileLine = sr.ReadLine();
    string[] t = null;
    #region
    // 循环，读取每一行
    while (fileLine != null)
    {
        // if the first non whitespace character is a #, ignore the line 
        // and go to the next line in the file 如行的第一个字符为“#”忽略这一行。直接读下一行。
        if (fileLine.Length > 0 && fileLine.Trim().Substring(0, 1) != "#")
        {
            // Read through the input line character by character 
            char lineChar;

            for (int i = 0; i < fileLine.Length; i++)
            {
                lineChar = fileLine[i];

                if (lineChar == '(')
                {
                    // //如果第一个字符是 "(" 整行放入 堆栈。
                    parens.Push(lineChar);
                }
                else if (lineChar == ')')
                {
                    // 如果字符是")",一个一个移出  （注：POP可在 Stack 的顶部移除一个元素）
                    parens.Pop();
                }
                else
                {
                    if (parens.Count == 0)
                    {

                        if (stringBuilder.Length > 0)
                        {
                            t = output.Split('=');
                            keyValues.Add((t.Length > 2 ? t[t.Length - 2] : t[0]).Trim(), stringBuilder.ToString());
                            stringBuilder.Clear();
                        }
                        output += lineChar;
                    }
                }
            }
            if (fileLine.IndexOf("(") > -1 || fileLine.IndexOf(")") > -1)
            {
                stringBuilder.Append(fileLine);
            }
        }
        fileLine = sr.ReadLine();
    }

    // Close the stream reader 
    sr.Close();
    return keyValues;
    #endregion
}

GetDatabases();