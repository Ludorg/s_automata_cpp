<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="text" indent="no"/>
    <xsl:template match="/automata">        
        <xsl:variable name="aut_n" select="./@name"/>
<!--        <xsl:text>inline void </xsl:text><xsl:value-of select="$aut_n"/>_init()<xsl:text>
{
</xsl:text>-->
        <xsl:text>  </xsl:text><xsl:value-of select="$aut_n"/>.init(<xsl:value-of select="initial_state"/>);<xsl:text>
</xsl:text>
        <xsl:for-each select="state">
            <xsl:variable name="st_from" select="./@name"/>
            <xsl:for-each select="to">
                <xsl:variable name="st_to" select="."/>
                <xsl:variable name="tr_evt" select="./@evt"/>
                <xsl:variable name="tr_act" select="./@action"/>
                    <xsl:text>  </xsl:text><xsl:value-of select="$aut_n"/>.addTransition(<xsl:value-of select="$st_from"/>, <xsl:value-of select="$st_to"/>, <xsl:value-of select="$tr_evt"/>, <xsl:value-of select="$tr_act"/>);<xsl:text>
</xsl:text>
            </xsl:for-each>
        </xsl:for-each>
        <!--<xsl:text>}
</xsl:text>-->
    </xsl:template>
</xsl:stylesheet>
