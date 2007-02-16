/*
 * $Id$
 *
 * SNMPStats Module 
 * Copyright (C) 2006 SOMA Networks, INC.
 * Written by: Jeffrey Magder (jmagder@somanetworks.com)
 *
 * This file is part of openser, a free SIP server.
 *
 * openser is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * openser is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 *
 * History:
 * --------
 * 2006-11-23 initial version (jmagder)
 * 2007-02-16 Moved all OID registrations from the experimental branch to 
 *            OpenSER's IANA assigned enterprise branch. (jmagder)
 * 
 * Note: this file originally auto-generated by mib2c using
 * mib2c.array-user.conf
 *
 * The file implements the openserSIPStatusCodesTable.  For a full description
 * of the table, please see the OPENSER-SIP-COMMON-MIB.
 *
 * This file consists of many more functions than the other header files.  
 * This is because this table is writable, bringing a lot of SNMP overhead.
 *
 * Most of the contents are auto-generated (aside from white space and comment
 * changes), and can be ignored.  The functions that have been modified are:
 *
 * 1) openserSIPStatusCodesTable_create_row()
 *
 * 2) openserSIPStatusCodesTable_extract_index() 
 *
 * 3) openserSIPStatusCodesTable_can_[activate|deactivate|delete]()
 *   
 * 4) openserSIPStatusCodesTable_set_reserve1()
 *
 * 5) openserSIPStatusCodesTable_get_value()
 *
 * Full details can be found in openserSIPStatusCodesTable.c.  You can safely
 * ignore the other functions.
 *
 */

#ifndef OPENSERSIPSTATUSCODESTABLE_H
#define OPENSERSIPSTATUSCODESTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

	
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

#include "../../config.h"

/* 
 * The structure has been mostly auto-generated, but its semantics have been
 * changed.  
 *
 * Specifically, the openserSIPStatusCodeIns and openserSIPStatusCodeOuts
 * variables don't store the total number of messages sent or received from the
 * system at the time of a SNMP GET request.  Instead, they store the number of
 * messages in or out (with respect to the message code specified by
 * openserSIPStatusCodeValue) at the time of the rows *creation*. 
 *
 * When the get request is received, the statistics framework will be queried,
 * and these values subtracted from that query.  This effectively gives us how
 * many of the given message codes have occured since the creation of the row,
 * insead of since OpenSER first loaded up.
 */
typedef struct openserSIPStatusCodesTable_context_s {
	
	/* The container interface requires that this be first. */
	netsnmp_index index; 

	/* The first index. */
	unsigned long openserSIPStatusCodeMethod;
	
	/* The second index, specifying which status code to monitor */
	unsigned long openserSIPStatusCodeValue;

	/* Stores the current status code value - startingInStatusCodeValue 
	 * (at the time this row was created)  */
	unsigned long openserSIPStatusCodeIns;

	/* Stores the current status code value - startingOutStatusCodeValue 
	 * (at the time this row was created)  */
	unsigned long openserSIPStatusCodeOuts;

	/* Initialized to zero at startup to signify uninitialized.  This can
	 * only be assigned createAndGo(4) at this point.  It can also be 
	 * assigned destroy(6), but only if the value is in the active(1) state.
	 */
	long openserSIPStatusCodeRowStatus;

	/* Added automatically, but not really used by us. */
	void * data;

	long startingInStatusCodeValue;
	long startingOutStatusCodeValue;

} openserSIPStatusCodesTable_context;

/* 
 * Initializes the openserSIPStatusCodesTable module.  This step is easier
 * than in the other tables because there is no table population.  All table
 * population takes place during run time. 
 */
void init_openserSIPStatusCodesTable(void);

/*
 * Initialize the openserSIPStatusCodesTable table by defining how it is
 * structured. 
 *
 * This function is mostly auto-generated.
 */
void initialize_table_openserSIPStatusCodesTable(void);

/*
 * This function is called to handle SNMP GET requests.  
 *
 * The row which this function is called with, will store a message code.  The
 * function will retrieve the 'number of messages in' and 'number of messages
 * out' statistic for this particular message code from the statistics
 * framework.  
 *
 * The function will then subtract from this value the value it was initialized
 * with when the row was first created.  In this sense, the row shows how many
 * ins and how many outs have been received (With respect to the message code)
 * since this row was created. 
 */
int   openserSIPStatusCodesTable_get_value(netsnmp_request_info *, 
		netsnmp_index *, netsnmp_table_request_info *);

const openserSIPStatusCodesTable_context * 
	openserSIPStatusCodesTable_get_by_idx(netsnmp_index *);

const openserSIPStatusCodesTable_context * 
	openserSIPStatusCodesTable_get_by_idx_rs(netsnmp_index *, 
			int row_status);

/* oid declarations */
extern oid openserSIPStatusCodesTable_oid[];
extern size_t openserSIPStatusCodesTable_oid_len;

#define openserSIPStatusCodesTable_TABLE_OID OPENSER_OID,3,1,1,1,5,1
	
/* column number definitions for table openserSIPStatusCodesTable */
#define COLUMN_OPENSERSIPSTATUSCODEMETHOD    1
#define COLUMN_OPENSERSIPSTATUSCODEVALUE     2
#define COLUMN_OPENSERSIPSTATUSCODEINS       3
#define COLUMN_OPENSERSIPSTATUSCODEOUTS      4
#define COLUMN_OPENSERSIPSTATUSCODEROWSTATUS 5

#define openserSIPStatusCodesTable_COL_MIN 3
#define openserSIPStatusCodesTable_COL_MAX 5

/* Handles index extraction for row creation */
int openserSIPStatusCodesTable_extract_index( 
		openserSIPStatusCodesTable_context * ctx, netsnmp_index * hdr );

/* Handle RESERVE1 and RESERVE2 phases of an SNMP SET */
void openserSIPStatusCodesTable_set_reserve1( netsnmp_request_group * );
void openserSIPStatusCodesTable_set_reserve2( netsnmp_request_group * );

/* Handle the SET and ACTION phases of an SNMP SET */
void openserSIPStatusCodesTable_set_action( netsnmp_request_group * );
void openserSIPStatusCodesTable_set_commit( netsnmp_request_group * );

/* Handle Resource cleanup if the ACTION or RESERVE1/RESERVE2 phases of an
 * SNMPSET fail */
void openserSIPStatusCodesTable_set_free( netsnmp_request_group * );
void openserSIPStatusCodesTable_set_undo( netsnmp_request_group * );

openserSIPStatusCodesTable_context * openserSIPStatusCodesTable_duplicate_row(
		openserSIPStatusCodesTable_context* );


netsnmp_index * openserSIPStatusCodesTable_delete_row( 
		openserSIPStatusCodesTable_context* );

/* Used to check if there is a reason why a row can't be activated 
 * (There is no reason in our implementation)
 */
int openserSIPStatusCodesTable_can_activate(
		openserSIPStatusCodesTable_context *undo_ctx,
		openserSIPStatusCodesTable_context *row_ctx,
		netsnmp_request_group * rg);

/* Used to check if there is a reason why a row can't be deactivated 
 * (There is no reason in our implementation)
 */
int openserSIPStatusCodesTable_can_deactivate(
		openserSIPStatusCodesTable_context *undo_ctx,
		openserSIPStatusCodesTable_context *row_ctx,
		netsnmp_request_group * rg);

/* Used to check if there is a reason why a row can't be deleted
 * (There is no reason in our implementation)
 */
int openserSIPStatusCodesTable_can_delete(
		openserSIPStatusCodesTable_context *undo_ctx,
		openserSIPStatusCodesTable_context *row_ctx,
		netsnmp_request_group * rg);
	
	
openserSIPStatusCodesTable_context * 
		openserSIPStatusCodesTable_create_row( netsnmp_index* );


#ifdef __cplusplus
}
#endif

#endif /** OPENSERSIPSTATUSCODESTABLE_H */
