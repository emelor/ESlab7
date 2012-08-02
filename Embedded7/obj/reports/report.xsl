<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" version="1.0" encoding="utf-8" indent="yes"/>

<!-- Root match -->
<xsl:template match="/">
  <html>
    <body>
      <xsl:apply-templates select="document"/>
    </body>
  </html>
</xsl:template>

<!-- document match -->
<xsl:template match="document">
  <xsl:apply-templates select="Header"/>
  <xsl:apply-templates select="Section">
    <xsl:sort data-type="number" select="@Index"></xsl:sort>
  </xsl:apply-templates>
</xsl:template>

<!-- Header match -->
<xsl:template match="Header">
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <link rel="stylesheet" type="text/css" href="./report.css" />
  <title><xsl:value-of select="@Plugin"/></title>

  <h1><xsl:value-of select="@Name"/></h1>

  <p>Date Created: <xsl:value-of select="@Date"/><br />
     Time Created: <xsl:value-of select="@Time"/>
  </p>

  <table border="0" width="80%" cellspacing="0" cellpadding="0">
    <tr bgcolor="#66CCFF">
      <td width="20%">Plugin Description</td>
      <td width="60%">Plugin Value</td>
    </tr>
    <tr>
      <td width="20%">Plugin Name</td>
      <td width="60%"><xsl:value-of select="@Plugin"/></td>
    </tr>
    <tr>
      <td width="20%">Plugin Platform</td>
      <td width="60%"><xsl:value-of select="@Platform"/></td>
    </tr>
    <tr>
      <td width="20%">Plugin Description</td>
      <td width="60%"><xsl:value-of select="@Description"/></td>
    </tr>
    <tr>
      <td width="20%">Plugin Version</td>
      <td width="60%"><xsl:value-of select="@Version"/></td>
    </tr>
  </table>
</xsl:template>

<!-- Section match -->
<xsl:template match="Section">
  <h2><xsl:value-of select="@Name"/></h2>

  <xsl:for-each select="Group">
    <xsl:sort data-type="number" select="@Index"></xsl:sort>
    <h3><xsl:value-of select="@Name"/></h3>

    <table border="0" width="80%" cellspacing="0" cellpadding="0">
      <tr bgcolor="#66CCFF">
        <td width="20%">Name</td>
        <td width="60%">Value</td>
      </tr>
      <xsl:for-each select="Entry">
        <xsl:sort data-type="number" select="@Index"></xsl:sort>
        <tr>
          <td width="20%">
            <xsl:value-of select="@Name"/>
          </td>
          <xsl:variable name="link" select="Link"/>
          <xsl:choose>
            <xsl:when test='$link'>
              <td width="60%">
                <a>
                  <xsl:attribute name="href"><xsl:value-of select="Link/@Path"/></xsl:attribute>
                  <xsl:value-of select="Link/@Name"/>
                </a>
              </td>
            </xsl:when>
            <xsl:otherwise>
              <xsl:choose>
                <xsl:when test="@Value='ERROR'">
                  <td width="60%" bgcolor="#DD0000" style="color:white">Failure</td>
                </xsl:when>
                <xsl:when test="@Value='OK'">
                  <td width="60%" bgcolor="#00DD00" style="color:white">Ok</td>
                </xsl:when>
                <xsl:when test="@Value='WARNING'">
                  <td width="60%" bgcolor="#FF7E00" style="color:white">Warning</td>
                </xsl:when>
                <xsl:otherwise>
                  <td width="60%"><xsl:value-of select="@Value"/></td>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:otherwise>
          </xsl:choose>
        </tr>
      </xsl:for-each>

    </table>
  </xsl:for-each>

</xsl:template>

</xsl:stylesheet>
