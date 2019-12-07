/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "fattoreX.h"

bool_t
xdr_Candidato(xdrs, objp)
	XDR *xdrs;
	Candidato *objp;
{

	if (!xdr_vector(xdrs, (char *)objp->candidato, 32, sizeof(char), (xdrproc_t)xdr_char))
		return (FALSE);
	if (!xdr_vector(xdrs, (char *)objp->giudice, 32, sizeof(char), (xdrproc_t)xdr_char))
		return (FALSE);
	if (!xdr_char(xdrs, &objp->categoria))
		return (FALSE);
	if (!xdr_vector(xdrs, (char *)objp->nomeFile, 32, sizeof(char), (xdrproc_t)xdr_char))
		return (FALSE);
	if (!xdr_char(xdrs, &objp->fase))
		return (FALSE);
	if (!xdr_int(xdrs, &objp->voto))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_Candidati(xdrs, objp)
	XDR *xdrs;
	Candidati *objp;
{

	if (!xdr_vector(xdrs, (char *)objp->candidato, MAXCANDIDATI, sizeof(Candidato), (xdrproc_t)xdr_Candidato))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_Giudice(xdrs, objp)
	XDR *xdrs;
	Giudice *objp;
{

	if (!xdr_vector(xdrs, (char *)objp->nomeGiudice, 32, sizeof(char), (xdrproc_t)xdr_char))
		return (FALSE);
	if (!xdr_int(xdrs, &objp->punteggio))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_Output(xdrs, objp)
	XDR *xdrs;
	Output *objp;
{

	if (!xdr_vector(xdrs, (char *)objp->giudici, MAXGIUDICI, sizeof(Giudice), (xdrproc_t)xdr_Giudice))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_Input(xdrs, objp)
	XDR *xdrs;
	Input *objp;
{

	if (!xdr_vector(xdrs, (char *)objp->candidato, 32, sizeof(char), (xdrproc_t)xdr_char))
		return (FALSE);
	if (!xdr_char(xdrs, &objp->operazione))
		return (FALSE);
	return (TRUE);
}
