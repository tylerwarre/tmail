# Generate CA cert & key
`C:\Users\M83393\libs\openssl-3.6.1\apps\openssl.exe req -x509 -newkey rsa:4096 -keyout .\certs\ca-key.pem -out .\certs\ca-cert.pem -config .\openssl.cnf`

# Generate client/server cert & key and sign with CA
`C:\Users\M83393\libs\openssl-3.6.1\apps\openssl.exe req -CA .\certs\ca-cert.pem -CAkey .\certs\ca-key.pem -noenc -newkey rsa:4096 -keyout .\certs\ca-key.pem -out .\certs\ca-cert.pem -config .\openssl.cnf`

# Verify Cert
`C:\Users\M83393\libs\openssl-3.6.1\apps\openssl.exe x509 -in .\certs\relay-cert.pem -text -noout`

